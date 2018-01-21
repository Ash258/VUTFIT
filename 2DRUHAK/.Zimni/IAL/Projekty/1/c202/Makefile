PRJ    = c202
PROGS  = $(PRJ)-test
CC     = gcc
CFLAGS = -Wall -std=c99 -pedantic -lm

all: clean $(PROGS)

$(PRJ)-test: $(PRJ).c $(PRJ)-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test.c
	./c202-test > cosi.txt

clean:
	rm -f *.o *.out $(PROGS)
