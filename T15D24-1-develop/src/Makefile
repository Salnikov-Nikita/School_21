CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
LDFLAGS=

all: build_db

build_db: ../build/modules_db

../build/modules_db: modules_db.o shared.o database.o modules.o levels.o status_events.o table.o stack.o
	$(CC) $(LDFLAGS) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ../build/* *.o

rebuild:
	$(MAKE) clean
	$(MAKE) all

.PHONY: all clean rebuild build_db