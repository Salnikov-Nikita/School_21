CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
LDFLAGS=

all: print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

print_module: ../build/Quest_1
documentation_module: ../build/Quest_2
bst_create_test: ../build/Quest_3
bst_insert_test: ../build/Quest_4
bst_traverse_test: ../build/Quest_5

../build/Quest_1: main_module_entry_point_1.o print_module.o
	$(CC) $(LDLAGS) $^ -o $@

../build/Quest_2: main_module_entry_point_2.o print_module.o documentation_module.o
	$(CC) $(LDLAGS) $^ -o $@

../build/Quest_3: bst_create_test.o bst.o
	$(CC) $(LDLAGS) $^ -o $@

../build/Quest_4: bst_insert_test.o bst.o
	$(CC) $(LDLAGS) $^ -o $@

../build/Quest_5: bst_traverse_test.o bst.o
	$(CC) $(LDLAGS) $^ -o $@

main_module_entry_point_%.o: main_module_entry_point.c
	$(CC) $(CFLAGS) -DQUEST_$* $< -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o ../build/Quest_*

rebuild:
	$(MAKE) clean
	$(MAKE) all

.PHONY: all clean rebuild print_module documentation_module bst_create_test bst_insert_test bst_traverse_test
