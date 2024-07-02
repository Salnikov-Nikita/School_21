CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
LDFLAGS=

all: state_sort state_search clear_state

state_sort: ../build/Quest_1
state_search: ../build/Quest_2
clear_state: ../build/Quest_3

../build/Quest_1: state_sort.o entry.o
	$(CC) $(LDFLAGS) $^ -o $@

../build/Quest_2: state_search.o entry.o
	$(CC) $(LDFLAGS) $^ -o $@

../build/Quest_3: clear_state.o entry.o
	$(CC) $(LDFLAGS) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ../build/* *.o

rebuild:
	$(MAKE) clean
	$(MAKE) all

.PHONY: all clean rebuild state_sort state_search clear_state