CC=gcc
CFLAGS=-Wall -pedantic -g

test: test.c bst.c
		$(CC) $(CFLAGS) -o test test.c bst.c

.PHONY:clean
clean:
		rm -f *.o test

