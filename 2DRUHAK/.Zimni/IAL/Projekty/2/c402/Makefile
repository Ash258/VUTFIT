PRJ    = c402
PROGS  = $(PRJ)-test
CC     = gcc
CFLAGS = -Wall -std=c99 -pedantic -lm

all: clean $(PROGS)

$(PRJ)-test: $(PRJ).c $(PRJ)-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test.c
#	./$(PRJ)-test > cosi.txt
#	diff cosi.txt c402-test.output

$(PRJ)-advanced-test: $(PRJ).c $(PRJ)-advanced-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-advanced-test.c

clean:
	rm -f *.o *.out $(PROGS)
