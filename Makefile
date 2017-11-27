CC = gcc
CDEBUG = -g
CFLAGS = -w
CLIBS = -lreadline

all:
	mkdir -p ./build/
	$(CC) $(CDEBUG) $(CFLAGS) -o ./build/a ./src/*.c -I./include $(CLIBS)
