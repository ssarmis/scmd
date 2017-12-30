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

#ifndef COMMAND_H
#define COMMAND_H

#define MAX_LINE_SIZE (1 << 10)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "commandlist.h"
#include "file/file.h"


static pid_t pid;

static int mainPipe[2];

static uint32_t kids;

void initPipe();
void initForkKid();
void initCommander();

void execRedir(const char** lh, const char* redirect);
void execParams(const char** args, int spaces, const char* path);
void execLinux(const char* cmd,  const char* path);

void waitForKids();

void waitInput();

uint32_t getKids();

#endif // COMMAND_H
