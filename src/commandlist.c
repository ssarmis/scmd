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

void commandNl(int argc, const char* args[128]){

	char sep = '\t';

	if(argc > 1){
		if(args[1][0] == '-'){
			if(args[1][1] == 's')
				sep = args[1][2];	
		}

		int fd = open(args[argc - 1], O_RDONLY);

		char* buffer = (char*)malloc(MAX_FILE_SIZE * sizeof(char));

		int rd = 0;

		while((rd = read(fd, buffer, MAX_FILE_SIZE)) > 0){
			buffer[rd] = 0;
		}
		close(fd);

		buffer = strtok(buffer, "\n");
		int count = 0;
		while(buffer != NULL){
	
			printf("%d%c%s\n", count++, sep, buffer);		
	
			buffer = strtok(NULL, "\n");
		}
	} else {
		printf("nl: not enough parameters provided.");	
	}

}

void commandMv(const char* args[128]){
	
	int src;
	int dest;

	src = open(args[1], O_RDONLY);
	dest = open(args[2], O_TRUNC | O_CREAT | O_RDWR, S_IWUSR);
	
	if(rename(src, dest) == -1){
		printf("%d\n", errno);
	}

	unlink(src);

	close(src);
	close(dest);

}

void commandCd(const char* args[128]){
	int ch = chdir(args[1]);
	if(ch != 0) {
		printf("Something didn't really work here...\n");	
	}
}







