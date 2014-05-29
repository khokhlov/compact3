set terminal pdf size 10cm,5cm
set output "rect2.pdf"

#set size 2, 2

unset border
unset grid
set yrange[-0.1:1.1]
unset key
unset xtic
unset ytic
set format x ''
set format y ''

set tmargin 0
set bmargin 0
set lmargin 1
set rmargin 1

set multiplot layout 1,4 rowsfirst

set label 1 'а)' at graph 0.86,0.9 font ',12'
plot "none.txt" with line lt 1 lc rgb "black" lw 1, \
	"cir.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0

set label 1 'б)' at graph 0.86,0.9 font ',12'
plot "none.txt" with line lt 1 lc rgb "black" lw 1, \
	"cip.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0

set label 1 'в)' at graph 0.86,0.9 font ',12'
plot "none.txt" with line lt 1 lc rgb "black" lw 1, \
    "bis1.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0

set label 1 'г)' at graph 0.86,0.9 font ',12'
plot "none.txt" with line lt 1 lc rgb "black" lw 1, \
    "bis2.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0


unset multiplot

set output
