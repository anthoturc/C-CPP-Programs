CC = gcc
CFLAGS = -Wall -g -pedantic

fs-find:fs-find.c
	$(CC) $(CFLAGS) -o fs-find fs-find.c fs-util.c

.PHONY:clean
clean:
	rm -f *.o fs-find

