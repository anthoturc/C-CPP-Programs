CC=g++

CPPFLAGS=-Wall -pedantic -g

test: test.cpp heap.cpp
		$(CC) $(CPPFLAGS) -o test.c heap.c

.PHONY:clean
clean:
		rm -f *.o test
