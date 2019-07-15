CC=gcc
CFLAGS=-Wall -pedantic -g

test:test.c list.c
		$(CC) $(CFLAGS) -o test test.c list.c

.PHONY:clean
clean:
		rm -f test
