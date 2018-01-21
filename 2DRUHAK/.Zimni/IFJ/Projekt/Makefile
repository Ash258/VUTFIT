## ********************************************************************
## Project:         Implementace překladače imperativního jazyka IFJ17.
## File:            Makefile
## Assignment:      125, I
## Date:            04/10/2017
## Authors:
##                  Pavel Parma         xparma02
##                  Vojtěch Bargl       xbargl01
##                  Jakub Čábera        xcaber00
##                  Tomáš Vondráček     xvondr23
## ********************************************************************

PROJ         = IFJ2017
CC           = gcc
CFLAGS       = -std=c11 -Wall -Werror -Wpedantic -lm
FINALZIPNAME = xparma02.zip
ZIPOUT       = ziptest
TMP          = tempZip.zip
# Get all c files excepts temporary files, generated files, etc...
SOURCES      = $(shell find . -name '*.c' \
                              -not -path '*tests*' \
                              -not -path '*cmake*' \
                              -not -path '*sandbox*' \
                              -not -path '*.idea*' \
                              -not -path '*$(ZIPOUT)*' \
                              -not -path '*symtable.c' \
                              -not -path '*symtable.h' \
                              -not -path '*tmp*')
# Convert c files into object files
OBJECTS      = $(SOURCES:%.c=%.o)
TESTFILES    = $(shell find tests/ -name "*.test.c")
UNITS        = All_units
ACCEPTS      = All_accepts
ZIPFILES     = Makefile rozdeleni rozsireni dokumentace.pdf
INCL         = fix_includes.sh

all: $(PROJ)

.PHONY: clean accept unit

## Build project.
$(PROJ): $(SOURCES)
	$(CC) $^ -o $@ $(CFLAGS) -DNDEBUG

## Enable debug macros.
debug: $(SOURCES)
	$(CC) $^ -o $@ $(CFLAGS)

## Remove all generated files.
clean:
	rm -rf $(PROJ) $(UNITS) $(ZIPOUT) $(FINALZIPNAME) ./tmp/ debug

## Copy all source files into temporary folder.
prepareFilesForSubmitting: clean
	mkdir ./tmp
	cd src/ && zip -rj ../tmp/$(TMP) *.c *.h **/*.c **/*.h
	cd ./tmp/ && unzip $(TMP) && rm -f $(TMP)
	cd ./bin/ && chmod +x ./$(INCL) && ./$(INCL)

## Zip project.
zip: prepareFilesForSubmitting
	zip -rj $(FINALZIPNAME) $(ZIPFILES)
	cd ./tmp/ && zip -r ../$(FINALZIPNAME) *.c *.h

## Run unit tests.
unit: clean
ifneq ($(file),)
	$(CC) $(CFLAGS) -o $(UNITS) $(file) -lcriterion; \
	./$(UNITS) $(args);
else
	@$(foreach file, $(TESTFILES), $(CC) $(CFLAGS) -o $(UNITS) $(file) -lcriterion; \
	./$(UNITS) $(args);)
endif

## Run acceptance tests.
accept: $(PROJ)
	@cd ./tests/Acceptance \
		&& chmod +x $(ACCEPTS).sh \
		&& ./$(ACCEPTS).sh ../../$(PROJ) $(args) $(file)

## Final archive tests.
testZip: clean zip
	chmod +x ./bin/is_it_ok.sh
	./bin/is_it_ok.sh $(FINALZIPNAME) $(ZIPOUT)

## Validate if packed version could be compiled (tests are irrelevant).
## Zip files => Validate zip structure => Run project binary made from zip (Working and ready to submit into WIS).
runFromZip: testZip
	cd $(ZIPOUT) && ./$(PROJ) ignored

## Every test must pass before submitting:
##     Could project be build without error?
##     Will unit tests pass?
##     Will acceptance tests pass?
##     It's possible to run project from submited zip?
submitCheck: clean $(PROJ) unit accept runFromZip

# End of Makefile
