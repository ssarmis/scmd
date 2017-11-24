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

// @CleanUp

#include "file/file.h"
#include "command/command.h"
#include "command/history.h"

// @TODO add doc

int main(int argc, char** argv){

	/* use system call to make terminal send all keystrokes directly to stdin */
	// system ("/bin/stty raw");
	initHistory();
	initCommander();

	while(1){
		printPointer();
		waitInput();
		waitForKids();
	}

	return 0;
}
