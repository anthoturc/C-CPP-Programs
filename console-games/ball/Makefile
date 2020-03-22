CC=gcc
CFLAGS=-Wall -pedantic
LDFLAGS=-lncurses

ball-bounce : ball-bounce.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY : clean
clean:
	rm -f ball-bounce ball