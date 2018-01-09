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


#include <readline/readline.h>

#ifdef USING_NETWORK
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
#endif // USING_NETWORK

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "command/command.h"


int main(int argc, char** argv){

	initPipe();

	rl_bind_key('\t',rl_abort);
	initCommander();

	while(1){
		waitInput();
	}

	return 0;
}

