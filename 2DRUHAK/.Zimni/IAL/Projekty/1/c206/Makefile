PRJ    = c206
PROGS  = $(PRJ)-test
CC     = gcc
CFLAGS = -Wall -std=c99 -pedantic -lm

all: clean $(PROGS)

$(PRJ)-test: $(PRJ).c $(PRJ)-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test.c
	./c206-test > cosi.txt

clean:
	rm -f *.o *.out $(PROGS)
