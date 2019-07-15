CC=gcc
CFLAGS=-Wall -pedantic -g 
INCLUDE=../LinkedList/SinglyLinked/

test:test.c stack.c
		$(CC) $(CFLAGS) -o test test.c stack.c $(INCLUDE)list.c -I$(INCLUDE)   

.PHONY:clean
clean:
		rm -f *.o test
