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

void commandNl(const char* args[128]){

	int fd = open(args[1], O_RDONLY);

	char* buffer = (char*)malloc(MAX_FILE_SIZE * sizeof(char));

	int rd = 0;

	while(read(fd, buffer, MAX_FILE_SIZE)){
		buffer[rd] = 0;
	}

	close(fd);

	buffer = strtok(buffer, "\n");
	int count = 0;
	while(buffer != NULL){

		printf("%d %s", count++, buffer);		

		buffer = strtok(NULL, "\n");
	}

}

void commandMv(const char* args[128]){
	
	

}
