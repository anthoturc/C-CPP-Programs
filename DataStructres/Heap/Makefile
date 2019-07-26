CC=g++

CPPFLAGS=-Wall -pedantic -g

test: test.cpp heap.cpp
	$(CC) $(CPPFLAGS) -o test test.cpp heap.cpp

.PHONY:clean
clean:
	rm -f *.o test
