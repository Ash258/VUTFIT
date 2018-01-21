PRJ      = c204
C202PATH = ../c202/
PROGS    = $(PRJ)-test
CC       = gcc
CFLAGS   = -Wall -std=c99 -pedantic -lm -I$(C202PATH)

all: clean $(PROGS)

$(PRJ)-test: $(PRJ).c $(PRJ)-test.c $(C202PATH)c202.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test.c $(C202PATH)c202.c
	./c204-test > cosi.txt

clean:
	rm -f *.o *.out $(PROGS)
