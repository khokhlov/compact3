set terminal pdf size 10cm,7cm
set output "tv_norm.pdf"

set grid
set key left bottom
set xlabel "Номер шага разностной схемы"
set ylabel "Норма TV"

plot "tv_cir.txt" with lp lt -1 pi 1 pt 1 ps 0.4 lc rgb "black" lw 1 ti "CIR", \
	"tv_cip.txt" with lp lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 1 ti "CIP", \
	"tv_bis1.txt" with lp lt -1 pi 1 pt 2 ps 0.4 lc rgb "black" lw 1 ti "БИС1", \
	"tv_bis2.txt" with line lt 1 lc rgb "black" lw 1 ti "БИС2"

set output
