EXEC=cola
CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
CFILES=testing.c cola.c pruebas_alumno.c main.c pila.c
HFILES=cola.h pila.h testing.h

all:
	$(CC) $(CFLAGS) $(CFILES) -o $(EXEC)
run: all
	./$(EXEC)
valgrind: all
	valgrind	$(VFLAGS)	./$(EXEC)
zip:
	zip $(EXEC).zip $(CFILES) $(HFILES)
