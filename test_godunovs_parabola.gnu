set terminal pdf size 10cm,5cm
set output "test_godunovs_parabola.pdf"

#set size 2, 2

set border
set grid
set yrange[-2:6]
set xrange[-3:4]
unset key
#unset xtic
#unset ytic
#set format x ''
#set format y ''

set tmargin 0
set bmargin 0
set lmargin 1
set rmargin 1

set multiplot layout 2,2 rowsfirst

set label 1 'CIR' at graph 0.1,0.1 font ',12'
plot "godunov_theor.txt" with line lt 1 lc rgb "black" lw 1, \
	"godunov_cir.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0

set label 1 'CIP' at graph 0.1,0.1 font ',12'
plot "godunov_theor.txt" with line lt 1 lc rgb "black" lw 1, \
	"godunov_cip.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0

set label 1 'БИС1' at graph 0.1,0.1 font ',12'
plot "godunov_theor.txt" with line lt 1 lc rgb "black" lw 1, \
	"godunov_bis1.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0

set label 1 'БИС2' at graph 0.1,0.1 font ',12'
plot "godunov_theor.txt" with line lt 1 lc rgb "black" lw 1, \
	"godunov_bis2.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0


unset multiplot

set output
