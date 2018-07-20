EXEC=heap
cc=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
CFILES=testing.c heap.c pruebas_alumno.c main.c
HFILES=heap.h testing.h

all:
	$(CC) $(CFLAGS) $(CFILES) -o $(EXEC)
run: all
	./$(EXEC)
valgrind: all
	valgrind	$(VFLAGS)	./$(EXEC)
