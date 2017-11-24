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
	printf("$> ");
}

void waitInput(){
	
	char tmp = getch();
	// @FixMe
	switch(tmp){
		case '^[[A': // up arrow
			printf("up");
			break;

		case '^[[B': // down arrow
			printf("down");
			break;

		default:
			fputc(tmp, stdin);
			break;
	}
	
	char* buf = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);

	fgets(buf, MAX_LINE_SIZE, stdin);
	
	parseCommand(buf);

	free(buf);
}

///
/// function copied from https://www.daniweb.com
/// from user jaybhanderi 
/// equivalent for getch()

int getch(){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

///

void parseCommand(const char* cmd){

	char* tmp = cmd;
	int checker = 0;

	while(tmp = strstr(tmp, " ")){
		checker++;
		tmp++;
	}
	
	if(!checker) { // just one thing in the command line
		if(strlen(cmd) != 0){

			///
			/// Things get interpreted here VVV just one command so nothing too complicated
			/// no args, no nothing.
			///
			
			appendCommand(cmd);

			if (strcmp(cmd, "exit\n") == 0) commandExit();
			else if (strcmp(cmd, "hist\n") == 0) printHistory();
			// else if (strcmp(cmd, "...") != 0) command function
			// etc
			
		} else {
			printf("Could not read parse an empty command");
		}
	} else { // multiple things on the command line
		
	}

	// @CleanUp
	// @TODO if has at least one space we have a command, yey, implement this
	//printf("%d\n", checker);

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

