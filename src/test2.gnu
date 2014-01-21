set terminal pdf monochrome size 15cm,7cm
set output "grid_corvergence.pdf"

#set size 2, 2

set grid
set key right bottom
#set yrange[-0.3:1.3]
#unset key
#unset xtic
#unset ytic
#set format x ''
#set format y ''

set xlabel "Шаг сетки"
set ylabel "Ошибка"

set logscale

set multiplot layout 1,2 rowsfirst

set label 1 'а)' at graph 0.88,0.94 font ',16'
plot "cir.txt" u (1/$1):2 w lp lt 1 lw 1 ti 'CIR', \
  "cip.txt" u (1/$1):2 with lp lt 7 ps 0.7 ti 'CIP', \
  "bis1.txt" u (1/$1):2 with lp lt 6 ti 'БИС1', \
  "bis2.txt" u (1/$1):2 with lp lt 4 ti 'БИС2'

set label 1 'б)' at graph 0.88,0.94 font ',16'
plot "cir.txt" u (1/$1):4 w lp lt 1 lw 1 ti 'CIR', \
  "cip.txt" u (1/$1):4 with lp lt 7 ps 0.7 ti 'CIP', \
  "bis1.txt" u (1/$1):4 with lp lt 6 ti 'БИС1', \
  "bis2.txt" u (1/$1):4 with lp lt 4 ti 'БИС2'

unset multiplot

set output
