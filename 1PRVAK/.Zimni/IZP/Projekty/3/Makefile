CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror

proj3:
	$(CC) $(CFLAGS) proj3.c -o proj3 -lm

.PHONY: clean

clean:
	rm -rf proj3

no: clean
	$(CC) $(CFLAGS) -DNDEBUG proj3.c -o proj3 -lm


