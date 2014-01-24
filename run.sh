#!/bin/bash

gcc -O2 test1.c -o test1 -lm
gcc -O2 test2.c -o test2 -lm
gcc -O2 test3.c -o test3 -lm

./test1 > table1.tex
gnuplot test1.gnu
./test2
gnuplot test2.gnu
./test3


