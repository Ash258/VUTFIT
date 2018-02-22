#!/usr/bin/env bash

mkdir test258
cd test258

mkdir 1less100B
cd 1less100B
truncate -s 75 test_file.dat
cd ..

mkdir 2less1KiB
cd 2less1KiB
truncate -s 100 test_file.dat
cd ..

mkdir 3less10KiB
cd 3less10KiB
truncate -s 1024 test_file.dat
cd ..

mkdir 4less100KiB
cd 4less100KiB
truncate -s 10240 test_file.dat
cd ..

mkdir 5less1MiB
cd 5less1MiB
truncate -s 102400 test_file.dat
cd ..

mkdir 6less10MiB
cd 6less10MiB
truncate -s 1048576 test_file.dat
cd ..

mkdir 7less100MiB
cd 7less100MiB
truncate -s 10485760 test_file.dat
cd ..

mkdir 8less1GiB
cd 8less1GiB
truncate -s 104857600 test_file.dat
cd ..

mkdir 9more1GiB
cd 9more1GiB
truncate -s 1073741824 test_file.dat
cd ./..
