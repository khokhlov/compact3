set terminal pdf size 15cm,15cm
set output "base_schemas.pdf"

#set size 2, 2

set grid
set yrange[-0.3:1.3]
unset key
#unset xtic
#unset ytic
set format x ''
set format y ''

set multiplot layout 3,2 rowsfirst

set label 1 'a)' at graph 0.92,0.9 font ',12'
plot "none.txt" with line lt 1 lc rgb "black" lw 1, \
	"cir.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0

set label 1 'b)' at graph 0.92,0.9 font ',12'
plot "none.txt" with line lt 1 lc rgb "black" lw 1, \
	"cip.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0

set label 1 'c)' at graph 0.92,0.9 font ',12'
plot "none.txt" with line lt 1 lc rgb "black" lw 1, \
	"cip2l.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0

set label 1 'd)' at graph 0.92,0.9 font ',12'
plot "none.txt" with line lt 1 lc rgb "black" lw 1, \
	"cip2r.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0

set label 1 'e)' at graph 0.92,0.9 font ',12'
plot "none.txt" with line lt 1 lc rgb "black" lw 1, \
    "bis1.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0

set label 1 'f)' at graph 0.92,0.9 font ',12'
plot "none.txt" with line lt 1 lc rgb "black" lw 1, \
    "bis2.txt" with linespoints lt -1 pi 1 pt 7 ps 0.4 lc rgb "black" lw 0


unset multiplot



set output
