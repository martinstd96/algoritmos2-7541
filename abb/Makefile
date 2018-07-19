EXEC=abb
cc=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
CFILES=testing.c abb.c pruebas_alumno.c main.c pila.c hash.c lista.c
HFILES=abb.h pila.h testing.h hash.h lista.h

all:
	$(CC) $(CFLAGS) $(CFILES) -o $(EXEC)
run: all
	time -f %e ./$(EXEC)
valgrind: all
	time -f %e valgrind	$(VFLAGS)	./$(EXEC)
