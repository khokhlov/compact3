#!/bin/bash

gcc -O2 test1.c -o test1 -lm
gcc -O2 test2.c -o test2 -lm
gcc -O2 test3.c -o test3 -lm
gcc -O2 test4.c -o test4 -lm
gcc -O2 test5.c -o test5 -lm

gcc -O2 grid_convergence_complex.c -o grid_convergence_complex_20 -lm
gcc -O2 -DTIME=2000.0 grid_convergence_complex.c -o grid_convergence_complex_2000 -lm

gcc -O2 grid_convergence_rect.c -o grid_convergence_rect_20 -lm
gcc -O2 -DTIME=2000.0 grid_convergence_rect.c -o grid_convergence_rect_2000 -lm


./test1 > table1.tex
gnuplot test1.gnu
./test2
./test3
./test4
gnuplot test4.gnu
./test1 5 > table2.tex
gnuplot test5.gnu
./test5 > table5.tex
gnuplot test6.gnu
./grid_convergence_complex_20
./grid_convergence_complex_2000
./grid_convergence_rect_20
./grid_convergence_rect_2000
