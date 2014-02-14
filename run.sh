#!/bin/bash

gcc -O2 test1.c -o test1 -lm
gcc -O2 test2.c -o test2 -lm
gcc -O2 test3.c -o test3 -lm
gcc -O2 test4.c -o test4 -lm

./test1 > table1.tex
gnuplot test1.gnu
./test2
./test3
./test4
gnuplot test4.gnu
./test1 5 > table2.tex
gnuplot test5.gnu