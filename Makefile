all:
	gcc -Wall -std=c99 -o a5 building.c defs.h evidence.c ghost.c hunter.c main.c room.c

clean:
	rm a5
