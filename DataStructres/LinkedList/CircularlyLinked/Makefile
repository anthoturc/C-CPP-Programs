CC=gcc
CFLAGS=-Wall -pedantic -g

test: test.c clist.c
		$(CC) $(CFLAGS) -o test test.c clist.c

.PHONY:clean
clean:
		rm -f *.o test

