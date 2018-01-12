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

#include "command/commandlist.h"

void commandExit(){
	exit(0);
}

int commandNl(int argc, const char* args[128]){

	char sep = '\t';
	char* delimitator = (char*)malloc(2 * sizeof(char));

	delimitator[0] = '\n';
	delimitator[1] = '\0';

	if(argc > 1){

		for(int i = 1; i < argc - 1; i++){
			if(args[i][0] == '-'){
				switch(args[i][1]){
					case 's':
						sep = args[i][2];
						break;
					case 'd':
						delimitator[0] = args[i][2];
						break;
					default:
						break;
				}
			} 
		}

		int fd = open(args[argc - 1], O_RDONLY);

		if(fd == -1){
			return errno;
		}

		char* buffer = (char*)malloc(MAX_FILE_SIZE * sizeof(char));

		int rd = 0;

		while((rd = read(fd, buffer, MAX_FILE_SIZE)) > 0){
			buffer[rd] = 0;
		}

		close(fd);

		#if TRY_HARD
			if(rd <= 0){
				return errno;		
			}
		#endif

		buffer = strtok(buffer, delimitator);
		int count = 0;
		while(buffer != NULL){
	
			printf("%d%c%s\n", count++, sep, buffer);		
	
			buffer = strtok(NULL, delimitator);
		}
	} else {
		printf("nl: not enough parameters provided.\n");	
		return -1;
	}
	return 0;

}

int commandMv(int argc, const char* args[128]){
	
	
	if(argc > 2){
		char* src = args[argc - 2];
		char* dest = args[argc - 1];
		int needPrompt = 0;
		#if 0
		src = open(args[1], O_RDONLY);
		dest = open(args[2], O_TRUNC | O_CREAT | O_RDWR, S_IWUSR);
		#endif 
		
		if(args[1][0] == '-'){
			if(args[1][1] == 'i'){
				needPrompt = 1;
			}
		}

		if(needPrompt){
			if(access(dest, F_OK) != -1){
				printf("File already exists, do you wish to continue ? [y/n]\n");
				char c = getchar();
				switch(c){
					case 'n':
						return 0;
						break;
					case 'y':

						if(rename(src, dest) == -1){
							return errno;
						}
						unlink(src);

						break;
					default:
						printf("Maybe next time choose a valid response? Assumed 'n'.\n");
						return 0;
						break;
				}

			} else {
				if(rename(src, dest) == -1){
					return errno;
				}
				unlink(src);
			}
		} else {
			if(rename(src, dest) == -1){
				return errno;
			}
			unlink(src);
		}
	
		#if 0
		close(src);
		close(dest);
		#endif 
	} else {
		printf("mv: not enough parameters provided.\n");
		return -1;	
	}
	
	return 0;
}

void commandCd(const char* args[128]){
	int ch = chdir(args[1]);
	if(ch != 0) {
		printf("Something didn't really work here...\n");	
	}
}







