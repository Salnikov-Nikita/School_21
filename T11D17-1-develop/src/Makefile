CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
LDFLAGS=

all: door_struct list_test stack_test

door_struct: ../build/Quest_1
list_test: ../build/Quest_2
stack_test: ../build/Quest_3

../build/Quest_1: dmanager_module.o
	$(CC) $(LDLAGS) $^ -o $@

../build/Quest_2: list_test.o list.o
	$(CC) $(LDLAGS) $^ -o $@

../build/Quest_3: stack_test.o stack.o
	$(CC) $(LDLAGS) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o ../build/Quest_*

rebuild:
	$(MAKE) clean
	$(MAKE) all

.PHONY: all clean rebuild door_struct list_test stack_test
