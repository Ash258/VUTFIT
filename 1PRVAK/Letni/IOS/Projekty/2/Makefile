CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic -lpthread
FILES = Makefile proj2.c proj2.h

all: clean proj2

proj2:
	$(CC) $(CFLAGS) proj2.c -o proj2

clean:
	rm -rf proj2 proj2.out proj2.zip

zip: clean
	zip proj2.zip $(FILES)

check: all
	./proj2 1 1 50 0 0 0
	chmod +x ./check-syntax.sh
	./check-syntax.sh proj2.out

test: clean
	$(CC) $(CFLAGS) -DNDEBUG proj2.c -o proj2
