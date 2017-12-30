CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror

proj2: clean
	$(CC) $(CFLAGS) proj2.c -lm -o proj2

.PHONY: clean

clean:
	rm -rf proj2

test:
	chmod +x ./ukazka.sh
	./ukazka.sh
