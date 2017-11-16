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

void initCommander(){
	kids = 0;
}

void printPointer(){
	printf("\n$> ");
}

void waitInput(){
	char* buf = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);

	fgets(buf, MAX_LINE_SIZE, stdin);

	parseCommand(buf);

	free(buf);
}

void parseCommand(const char* cmd){

	char* tmp = cmd;
	int checker = 0;

	while(tmp = strstr(tmp, " ")){
		checker++;
		tmp++;
	}
	// @TODO if has at least one space we have a command, yey, implement this
	printf("%d\n", checker);

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
