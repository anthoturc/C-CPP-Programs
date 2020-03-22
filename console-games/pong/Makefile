CC=gcc
CFLAGS=-Wall -pedantic
LDFLAGS=-lncurses

pong : pong.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY : clean
clean:
	rm -f pong