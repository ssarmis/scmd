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

#ifndef HISTORY_H
#define HISTORY_H

#define HIST_FILE "scmd.hist"
#define MAX_LINE_SIZE (1 << 10)

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "file/file.h"

static file history;

void initHistory();
void printHistory();
void appendCommand(const char* cmd);


#endif // HISTORY_H
