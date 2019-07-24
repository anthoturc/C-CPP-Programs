CC=g++
CFLAGS=-Wall -pedantic -g

test: test.cpp trie.cpp
	$(CC) $(CFLAGS) -o test test.cpp trie.cpp

.PHONY:clean
clean:
	rm -f *.o test