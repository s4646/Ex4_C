.PHONY: all clean
CC = gcc
FLAGS= -Wall -Werror -g
OBJ = main.o graph.o
PROGS = main.o graph.o prog

all: $(PROGS)

prog: main.o graph.o
	$(CC) $(FLAGS) -o prog $(OBJ)

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c graph.h

graph.o: graph.c
	$(CC) $(FLAGS) -c graph.c

clean: 
	rm -f *.a *.o *.so prog