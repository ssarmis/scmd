CC=gcc
CFLAGS=-w

all:
	mkdir -p ./build/
	$(CC) $(CFLAGS) -o ./build/a ./src/*.c -I./include
