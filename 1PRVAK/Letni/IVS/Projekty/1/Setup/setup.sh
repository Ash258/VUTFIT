#!/usr/bin/env bash

rm CMakeCache.txt
cmake ..

make

ctest -C Debug

make white_box_test_coverage
make tdd_test_coverage

tar cfv xcaber00.zip ../black_box_tests.cpp ../white_box_tests.cpp ../tdd_code.h ../tdd_code.cpp
