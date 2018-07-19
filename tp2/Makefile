EXEC=tp2
CC=gcc
CFLAGS=-g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
CFILES=heap.c lista.c strutil.c tp2.c hash.c pila.c abb.c
HFILES=heap.h lista.h campo_archivo.h strutil.h hash.h pila.h abb.h

all:
	$(CC) $(CFLAGS) $(CFILES) -o $(EXEC)
run: all
	./$(EXEC) 1
valgrind: all
	valgrind	$(VFLAGS)	./$(EXEC) 1
