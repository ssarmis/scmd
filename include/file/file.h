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

#ifndef FILE_H
#define FILE_H

#define MAX_FILE_SIZE 	((1 << 10) * 10)

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


typedef struct file {

	int 		fileid;
	int	 	size;
	char* 	path;
	char* 	buf;

} file;


void openf(file* f, const char* path, uint32_t flags);

void createf(file* f, const char* path);

int writef(file* f, void* data, uint32_t size);

int readf(file* f);

void freef(file* f);

void closef(file* f);

void dumpf(const file* f);

#endif FILE_H
