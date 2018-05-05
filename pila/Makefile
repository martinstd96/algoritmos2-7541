EXEC=pila
CC=gcc
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
CFLAGS=-g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
CFILES=testing.c pila.c pruebas_alumno.c main.c
HFILES=pila.h testing.h

all:
	$(CC) $(CFLAGS) $(CFILES) -o $(EXEC)
run: all
	./$(EXEC)
valgrind: all
	valgrind	$(VFLAGS)	./$(EXEC)
zip:
	zip	$(EXEC).zip	$(CFILES)	$(HFILES)
