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

#include "command/history.h"

void initHistory(){
	createf(&history, HIST_FILE);
}

void printHistory(){
	closef(&history);

	openf(&history, HIST_FILE, O_RDONLY);

	readf(&history);

	printf("\n%s\n", history.buf);

	closef(&history);

	openf(&history, HIST_FILE, O_RDWR | O_APPEND);
}

void appendCommand(const char* cmd){
	writef(&history, cmd, strlen(cmd));
}


void goHistUp(){
	histLine--;
	if(histLine < 0) histLine = 0;
}

void goHistDown(){
	histLine++;
}

void printHistLine(){

	char sep[] = "\n";
	char* str;
	int i = 0;
	
	closef(&history);

	openf(&history, HIST_FILE, O_RDONLY);

	readf(&history);
	

	char* tmp = history.buf;
	
	while((str = strtok(tmp, sep)) != NULL){
		if(++i == histLine){			
			printf("\r$> %d %s", histLine, str);
			str = strtok(NULL, sep);
			break;
		}

	}

	closef(&history);
	openf(&history, HIST_FILE, O_RDWR | O_APPEND);
}





