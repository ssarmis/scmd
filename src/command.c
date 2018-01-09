//   scmd a simple and small unix shell
//
//	Copyright (C) 2017 Streanga Sarmis-Stefan.
//
//	This program is free software : you can redistribute it and / or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program, if not, see <http://www.gnu.org/licenses/>.

#include "command/command.h"

void initPipe(){
	pipe(mainPipe);
}


void initCommander(){
	kids = 0;
}

void initForkKid(){
	pid = fork();
	kids++;
}

void waitInput(){

	printf("%s", get_current_dir_name());
	char* buf = readline("$> ");
	
	parseCommand(buf);

	free(buf);
}


void parseCommand(const char* cmd){

	int checker = 0;
	add_history(cmd);
	
	if(strlen(cmd) != 0){

		
		char* tredir = strdup(cmd);
		
		int redirects = 0;
		int spaces = 0;
		int joins = 0; 

		/// Redirects	
		
		char* redirArgs[2]; // @TODO make this more flexible

		tredir = strtok(tredir, ">");

		while(tredir != NULL){
			redirArgs[redirects++] = tredir;
			tredir = strtok(NULL, ">");
		}

		/// end of redirects
		
		char* tspaces = strdup(redirArgs[0]);
		char* tjoins = strdup(redirArgs[0]);

		/// Multiple arguments	

		char* args[128]; // @TODO make this more flexible

		tspaces = strtok(tspaces, " ");

		while(tspaces != NULL){
			args[spaces++] = tspaces;
			tspaces = strtok(NULL, " ");
		}
		/// end of multiple arguments

		/// Joins

		char* joinArgs[12]; // @TODO make this more flexible

		tjoins = strtok(tjoins, "|");

		while(tjoins != NULL){
			joinArgs[joins++] = tjoins;	
			tjoins = strtok(NULL, "|");
		}
		/// end of joins


		if (strcmp(cmd, "exit") == 0){

			 commandExit();

		} else if(joins > 1 && redirects == 1){
			
			execInChain(joinArgs, joins, "\0");

		} else if(joins > 1 && redirects > 1){
			
			execInChain(joinArgs, joins, redirArgs[1]);

		} else if(spaces == 1 && redirects == 1){

			 execLinux(cmd, "\0");

		} else if(spaces > 1 && redirects == 1){

			execParams(args, spaces, "\0");

		} else if(spaces > 1 && redirects > 1){

			execParams(args, spaces, redirArgs[1]);

		}


	} else {
		// printf("Could not read parse an empty command\n");
	}

}


// void execRedir(const char** lh, const char* redirect){}

void execInChain(const char** args, int joins, const char* path){
	
	
	int redirect;

	char** cargs = args;
	int cmdIndex;
	
	if(path[0] != 0){
		redirect = open(path, O_TRUNC | O_CREAT | O_RDWR, 0666);
	}
	
	if(fork() == 0){

		int fileDesc[2];

		pid_t pid;

		int in = 0;
		int out = 1;

		for(cmdIndex = 0; cmdIndex < joins - 1; cmdIndex++){
			
			char* args[128]; // @TODO make this more flexible

			char* tspaces = cargs[cmdIndex];
			int spaces = 0;	
	
			tspaces = strtok(tspaces, " ");

			while(tspaces != NULL){
				args[spaces++] = tspaces;
				tspaces = strtok(NULL, " ");
			}

			args[spaces] = NULL;

			pipe(fileDesc);

			pid = fork();
	 			
		   	if(pid == 0) {

				out = fileDesc[1];
				
				if(in != 0){
					dup2(in, 0);
					close(in);
				}
			
				if(out != 1){
					dup2(out, 1);
					close(out);
				}


//				execvp(args[0], args);

				execParams(args, spaces, "\0");

				exit(0);
			}

			close(fileDesc[1]);

			in = fileDesc[0];

			wait();

		}

		char* args[128]; // @TODO make this more flexible

		char* tspaces = cargs[joins - 1];
		int spaces = 0;	

		tspaces = strtok(tspaces, " ");

		while(tspaces != NULL){
			args[spaces++] = tspaces;
			tspaces = strtok(NULL, " ");
		}

		args[spaces] = NULL;

		if(path[0] != 0){
			dup2(in, 0);	
			dup2(redirect, 1);
		} else {
			dup2(in, 0);	
		}

		execParams(args, spaces, "\0");

//		execvp(args[0], args);
	}
	wait();
	printf("\n");

	if(path[0] != 0){
		close(redirect);
	}

}

void execParams(const char** args, int spaces, const char* path){
	
	int redirect;	
	
	char** cargs = args;
	int words = spaces;
	int saved;	

	if(path[0] != 0){
		redirect = open(path, O_TRUNC | O_CREAT | O_RDWR, 0666);
		saved = dup(1);
		dup2(redirect, 1);
	}

	if(strcmp(cargs[0], "nl") == 0) {

		int suc = commandNl(words, cargs);
	
		printf("Executed with a returned code: %d\n", suc);

	} else if(strcmp(cargs[0], "mv") == 0) {

		int suc = commandMv(words, cargs);

		printf("Executed with a returned code: %d\n", suc);

	} else if(strcmp(cargs[0], "cd") == 0) {

		commandCd(cargs);

	} else {
		int totalSize = 0;

		for(int i = 0; i < words; i++){
			totalSize += strlen(cargs[i]);
		}


		char* cmd = (char*)malloc(totalSize * sizeof(char));
		memset(cmd, 0, (totalSize - 1) * sizeof(char));

		int i;
		
		for(i = 0; i < words; i++){
			strcat(cmd, cargs[i]);
			strcat(cmd, " ");
		}

		execLinux(cmd, "\0");
	}

	wait();

	if(path[0] != 0){
		close(redirect);
		dup2(saved, 1);
		close(saved);
	}

}

void execLinux(const char* cmd, const char* path){

	kids++;
	initForkKid();

	if(pid > 0){
		char* tmp = cmd;
		char* args[12];

		int num = 0;
		tmp = strtok(tmp, " ");

		while(tmp != NULL){
			args[num] = tmp;
			num++;

			tmp = strtok(NULL, " ");
		}
		num++;


		write(mainPipe[1], &num, sizeof(num));
		int i;

		for(i = 0; i < num - 1; i++){
			int size = strlen(args[i]);

			write(mainPipe[1], &size, sizeof(size));
			write(mainPipe[1], args[i], size);
		}

		waitForKids();

		// free(args); @FixMe seg fault


	} else if(pid == 0){
		
		int num;
		read(mainPipe[0], &num, sizeof(num));

		char** args = (char**)malloc((num) * sizeof(char*));

		int i;
		for(i = 0; i < num - 1; i++){
			/* I don't need this anymore, but maybe I want to reuse this.
			if(i == 0){
				int size;
				read(mainPipe[0], &size, sizeof(size));

				args[i] = (char*)malloc(size + 5 + 1);
				memset(args[i], 0, size + 5 + 1);					
				
				char* tmpc = (char*)malloc(size + 1);
				memset(tmpc, 0, size + 1);					
	
				read(mainPipe[0], tmpc, size);

				char* str1 = (char*)malloc(size + 5 + 1);
				memset(str1, 0, size + 5 + 1);					

				str1[0] = '/';
				str1[1] = 'b';
				str1[2] = 'i';
				str1[3] = 'n';
				str1[4] = '/';
	
				strcat(str1, tmpc);
	
				args[i] = str1;
			} else {
			*/

			int size;
			read(mainPipe[0], &size, sizeof(size));

			args[i] = (char*)malloc(size + 1);
			memset(args[i], 0, size + 1);					

			read(mainPipe[0], args[i], size);
		}

		args[num - 1] = NULL;

		execvp(args[0], args);

		printf("Could not execute !\n");

		exit(1);
	}

}

void waitForKids(){
	if (getKids() > 0){
		int i = 0;
		for(; i < getKids(); i++) wait();
	}
}

uint32_t getKids(){
	return kids;
}


