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

	char* buf = readline("$> ");
	
	parseCommand(buf);

	free(buf);
}


void parseCommand(const char* cmd){

	int checker = 0;
	add_history(cmd);
	
	if(strlen(cmd) != 0){

		
		char* tredir = strdup(cmd);
		char* tspaces = strdup(cmd);
		char* tjoins = strdup(cmd);

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


		if (strcmp(cmd, "exit") == 0) commandExit();
		else if(joins > 1){
			
			printf("%d, %s, %s, %d\n", joins, joinArgs[0], joinArgs[1], strlen(joinArgs[1]));
			execInChain(joinArgs, joins);
		
		} else if(redirects > 1){
			printf("this guy wants a redirect to %s\n", redirArgs[1]);
		} else if(spaces == 1 && redirects == 1) execLinux(cmd, 0);
		else if(spaces > 1 && redirects == 1){
			execParams(args, spaces, 0);
		}

	} else {
		// printf("Could not read parse an empty command\n");
	}

}


void execRedir(const char** lh, const char* redirect){}

void execInChain(const char** args, int joins){
	
	
	char** cargs = args;
	int cmdIndex;

	for(cmdIndex = 0; cmdIndex < joins; cmdIndex++){

		char* args[128]; // @TODO make this more flexible

		char* tspaces = cargs[cmdIndex];
		int spaces = 0;	
	
		tspaces = strtok(tspaces, " ");

		while(tspaces != NULL){
			args[spaces++] = tspaces;
			tspaces = strtok(NULL, " ");
		}

		execParams(args, spaces, 1);

	}


}

void execParams(const char** args, int spaces, int inPipe){
	
	char** cargs = args;
	int words = spaces;

	if(strcmp(cargs[0], "nl") == 0) commandNl(cargs);
	else {
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

		// printf("Command was not found, using linux shell instead.\n");
		execLinux(cmd, inPipe);
	}

}

void execLinux(const char* cmd, int inPipe){

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
		
		if(inPipe) dup2(mainPipe[0], stdin);

		int num;
		read(mainPipe[0], &num, sizeof(num));

		char** args = (char**)malloc((num) * sizeof(char*));

		int i;
		for(i = 0; i < num - 1; i++){
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
				int size;
				read(mainPipe[0], &size, sizeof(size));

				args[i] = (char*)malloc(size + 1);
				memset(args[i], 0, size + 1);					

				read(mainPipe[0], args[i], size);
			}
		}

		args[num - 1] = NULL;

		if(inPipe) dup2(mainPipe[1], stdout);

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


