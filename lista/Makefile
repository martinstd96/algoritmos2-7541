EXEC=lista
cc=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
CFILES=testing.c lista.c pruebas_alumno.c main.c pila.c
HFILES=lista.h pila.h testing.h

all:
	$(CC) $(CFLAGS) $(CFILES) -o $(EXEC)
run: all
	./$(EXEC)
valgrind: all
	valgrind	$(VFLAGS)	./$(EXEC)
zip:
	zip $(EXEC).zip $(CFILES) $(HFILES)
