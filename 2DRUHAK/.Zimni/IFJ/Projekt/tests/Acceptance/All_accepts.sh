#!/usr/bin/env bash

# Include All tests and Helpers
. Functions.sh

rm -f ${LOG} ${GENERATED_FILE} # Clean log file and generated file

if [ ! -z $3 ]; then
    base="${3#./tests/Acceptance/}"
    file=`find ./Suites/ -samefile ${base} -type f` # Get all test files
    executeTest $1 ${file} $2
    rm -f ${GENERATED_FILE}
    printAndExit
fi

FILES=`find ./Suites/ -name "*.IFJ" -type f` # Get all test files

for file in ${FILES}; do
    executeTest $1 ${file} $2
    rm -f ${GENERATED_FILE}
done

printAndExit
