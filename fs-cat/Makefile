CC = gcc
CFLAGS = -Wall -g -pedantic

fs-cat:fs-cat.c
	$(CC) $(CFLAGS) -o fs-cat fs-cat.c fs-util.c

.PHONY:clean
clean:
	rm -f *.o fs-cat

