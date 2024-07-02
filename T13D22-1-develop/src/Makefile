CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
LDFLAGS=

all: cipher

cipher: ../build/cipher

../build/cipher: cipher.o
	$(CC) $(LDFLAGS) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ../build/* *.o

rebuild:
	$(MAKE) clean
	$(MAKE) all

.PHONY: all clean rebuild cipher