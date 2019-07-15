CC=gcc
CFLAGS=-Wall -pedantic -g
INCLUDE=../LinkedList/SinglyLinked/

test: test.c queue.c
		$(CC) $(CFLAGS) -o test test.c queue.c $(INCLUDE)/list.c -I$(INCLUDE)

.PHONY:clean
clean:
		rm -f test *.o

