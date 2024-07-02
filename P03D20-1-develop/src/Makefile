CC=gcc
CFLAGS=-Wall -Wextra -Werror -g
BUILD=../build/

all: graph

graph: mystack.o parsing_in_polish_notation.o calculation.o draw.o graph.o
	$(CC) $(CFLAGS) mystack.o graph.o parsing_in_polish_notation.o draw.o calculation.o -o $(BUILD)graph

calculation.o: calculation.c calculation.h
	$(CC) $(CFLAGS)	calculation.c -c

draw.o: draw.c
	$(CC) $(CFLAGS)	draw.c -c

graph.o: graph.c
	$(CC) $(CFLAGS) graph.c -c

parsing_in_polish_notation.o: parsing_in_polish_notation.c
	$(CC) $(CFLAGS) parsing_in_polish_notation.c -c

mystack.o: mystack.c mystack.h
	$(CC) $(CFLAGS) mystack.c -c

clean:
	rm -rf *.o $(BUILD)graph

rebuild: clean all