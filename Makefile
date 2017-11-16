all:
	mkdir -p ./build/
	gcc -o ./build/a ./src/*.c -I./include -w
