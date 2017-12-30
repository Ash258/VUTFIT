#!/usr/bin/env bash

echo "Toto přepiš!"
N0_ERROR="Argument 'size' have to be > 0!\n"
HELP="Help: \nproj1 [-s <number>] [-n <number>] | to hex dump\nproj1 -S <number> | to print strings bigger than <number>\nproj1 -x | to convert characters to hexadecimal values\nproj1 -r | to convert hexadecimal values to characters\n"

clear
echo -e "\n --- PREPARATION --- \n"

make clean
make

rm -rf .test/*
mkdir -p ./test/

echo -e "\n --- TESTTING --- \n"

start='Test'
end='-'

function tmpFile {
    touch ./test/$1
    echo ./test/$1
}

function assertWhenDiffs {
    diff -q $1 $2
    diff $1 $2 > $3
}

echo ${start}"1"
echo "Hello, world! Ahoj svete!" | ./proj1 > $(tmpFile test1.res)
printf "00000000  48 65 6c 6c 6f 2c 20 77  6f 72 6c 64 21 20 41 68  |Hello, world! Ah|\n00000010  6f 6a 20 73 76 65 74 65  21 0a                    |oj svete!.      |\n" > $(tmpFile test1.exp)
assertWhenDiffs $(tmpFile test1.res) $(tmpFile test1.exp) $(tmpFile test1.diff)
echo ${end}

echo ${start}"2"
echo "Hello, world! Ahoj svete!" | ./proj1 -s 14 -n 5 > $(tmpFile test2.res)
echo "0000000e  41 68 6f 6a 20                                    |Ahoj            |" > $(tmpFile test2.exp)
assertWhenDiffs $(tmpFile test2.res) $(tmpFile test2.exp) $(tmpFile test2.diff)
echo ${end}

echo ${start}"3"
echo "Hello" | ./proj1 -x > $(tmpFile test3.res)
echo "48656c6c6f0a" > $(tmpFile test3.exp)
assertWhenDiffs $(tmpFile test3.res) $(tmpFile test3.exp) $(tmpFile test3.diff)
echo ${end}

echo ${start}"4"
printf 'Hello, world!\0Ahoj svete!\n\0AP\nABCD\n' | ./proj1 -S 3 > $(tmpFile test4.res)
printf "Hello, world!\nAhoj svete!\nABCD\n" > $(tmpFile test4.exp)
assertWhenDiffs $(tmpFile test4.res) $(tmpFile test4.exp) $(tmpFile test4.diff)
echo ${end}

echo ${start}"5"
echo "48 65 6c6c6f a" | ./proj1 -r > $(tmpFile test5.res)
printf "Hello\n\n" > $(tmpFile test5.exp)
assertWhenDiffs $(tmpFile test5.res) $(tmpFile test5.exp) $(tmpFile test5.diff)
echo ${end}

echo ${start}"6"
printf "\xff\x00" | ./proj1 -x > $(tmpFile test6.res)
echo "ff00" > $(tmpFile test6.exp)
assertWhenDiffs $(tmpFile test6.res) $(tmpFile test6.exp) $(tmpFile test6.diff)
echo ${end}

echo ${start}"7"
echo "Ahoj" | ./proj1 > $(tmpFile test7.res)
echo "00000000  41 68 6f 6a 0a                                    |Ahoj.           |" > $(tmpFile test7.exp)
assertWhenDiffs $(tmpFile test7.res) $(tmpFile test7.exp) $(tmpFile test7.diff)
echo ${end}

echo ${start}"8"
printf "Ahoj\0Slovo\nXY\n" | ./proj1 -S 3 > $(tmpFile test8.res)
printf "Ahoj\nSlovo\n" > $(tmpFile test8.exp)
assertWhenDiffs $(tmpFile test8.res) $(tmpFile test8.exp) $(tmpFile test8.diff)
echo ${end}

echo ${start}"9"
printf "00ff00ff\n" | ./proj1 -r | ./proj1 -x > $(tmpFile test9.res)
echo "00ff00ff0a" > $(tmpFile test9.exp)
assertWhenDiffs $(tmpFile test9.res) $(tmpFile test9.exp) $(tmpFile test9.diff)
echo ${end}

echo ${start}"10"
printf "" | ./proj1 > $(tmpFile test10.res)
echo "00000000                                                    |                |" > $(tmpFile test10.exp)
assertWhenDiffs $(tmpFile test10.res) $(tmpFile test10.exp) $(tmpFile test10.diff)
echo ${end}

echo ${start}"11"
printf "Nebere se v potaz" | ./proj1 -n 0 > $(tmpFile test11.res) 2>&1
printf "${N0_ERROR}" > $(tmpFile test11.exp)
assertWhenDiffs $(tmpFile test11.res) $(tmpFile test11.exp) $(tmpFile test11.diff)
echo ${end}

echo ${start}"12"
printf "12345" | ./proj1 -s 6 > $(tmpFile test12.res)
printf "" > $(tmpFile test12.exp)
assertWhenDiffs $(tmpFile test12.res) $(tmpFile test12.exp) $(tmpFile test12.diff)
echo ${end}

echo ${start}"13"
printf "" | ./proj1 -s 5 > $(tmpFile test13.res)
printf "" > $(tmpFile test13.exp)
assertWhenDiffs $(tmpFile test13.res) $(tmpFile test13.exp) $(tmpFile test13.diff)
echo ${end}

echo ${start}"14"
printf "Ahoj jak se máš, já se mám čarovně." | ./proj1 > $(tmpFile test14.res)
printf "00000000  41 68 6f 6a 20 6a 61 6b  20 73 65 20 6d c3 a1 c5  |Ahoj jak se m...|\n00000010  a1 2c 20 6a c3 a1 20 73  65 20 6d c3 a1 6d 20 c4  |., j.. se m..m .|\n00000020  8d 61 72 6f 76 6e c4 9b  2e                       |.arovn...       |\n" > $(tmpFile test14.exp)
assertWhenDiffs $(tmpFile test14.res) $(tmpFile test14.exp) $(tmpFile test14.diff)
echo ${end}

echo ${start}"15"
printf "Nebere se v potaz" | ./proj1 foo > $(tmpFile test15.res)
printf "${HELP}" > $(tmpFile test15.exp)
assertWhenDiffs $(tmpFile test15.res) $(tmpFile test15.exp) $(tmpFile test15.diff)
echo ${end}

echo ${start}"16"
printf "Tohle ma 16 znaku" | ./proj1 -n 16 > $(tmpFile test16.res)
printf "00000000  54 6f 68 6c 65 20 6d 61  20 31 36 20 7a 6e 61 6b  |Tohle ma 16 znak|\n" > $(tmpFile test16.exp)
assertWhenDiffs $(tmpFile test16.res) $(tmpFile test16.exp) $(tmpFile test16.diff)
echo ${end}