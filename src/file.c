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

#include "file/file.h"

void openf(file* f, const char* path, uint32_t flags){
	f->fileid = open(path, flags);
	f->path = path;

	if(f->fileid < 0){
		printf("Could not open file %s\n", path);
		exit(1);
	}
	
	f->buf = (char*)malloc(sizeof(char) * MAX_FILE_SIZE);

}

void createf(file* f, const char* path){
	openf(f, path, O_TRUNC | O_CREAT | O_WRONLY);
}

int readf(file* f){
	while((f->size = read(f->fileid, f->buf, MAX_FILE_SIZE - 1)) > 0){
		f->buf[f->size] = '\0';
	}
	
	if(f->size < 0){
		int errsv = errno;
		printf("Could not read file %s error %d\n", f->path, errsv);
	}

	return f->size;
}

int writef(file* f, void* data, uint32_t size){
	
	int wb = write(f->fileid, data, size);
	
	if(wb < 0){
		int errsv = errno;
		printf("Could not write file %s error %d\n", f->path, errsv);
	}

	return wb;
}

void freef(file* f){
	free(f->buf);
}

void closef(file* f){
	close(f->fileid);
}

void dumpf(const file* f){
	printf("\n%s\n", f->buf);
}
