CC=gcc
CFLAGS=-Wall -pedantic -g

test:test.c dlist.c
		$(CC) $(CFLAGS) -o test test.c dlist.c

.PHONY:clean
clean:
		rm -f test *.o
