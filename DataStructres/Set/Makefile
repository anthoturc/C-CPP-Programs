CC=gcc
CFLAGS=-Wall -pedantic -g
INCLUDE=-I../Tree/BinarySearchTree/

test: test.c set.c
		$(CC) $(CFLAGS) -o test test.c set.c $(INCLUDE)bst.c $(INCLUDE)

.PHONY:clean
clean:
		rm -f *.o test
