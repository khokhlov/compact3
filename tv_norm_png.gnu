set terminal png
set output "tv_norm.png"

set grid
set key left bottom
set xlabel "Номер шага разностной схемы"
set ylabel "Норма TV"

plot "tv_cir.txt" with line ti "CIR", \
	"tv_cip.txt" with line ti "CIP", \
	"tv_bis1.txt" with line ti "БИС1", \
	"tv_bis2.txt" with line ti "БИС2"

set output
