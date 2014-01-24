#!/bin/bash

gcc -O2 test1.c -o test1 -lm
gcc -O2 test2.c -o test2 -lm
gcc -O2 test3.c -o test3 -lm

./test1
./test2
./test3

gnuplot test1.gnu
gnuplot test2.gnu
