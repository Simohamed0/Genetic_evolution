set term png
set output "gravitationuniv.png"
set xrange[0:10000000]
set xlabel "Number of Evaluations"
set ylabel "Fitness"
plot 'gravitationuniv.dat' using 3:4 t 'Best Fitness' w lines, 'gravitationuniv.dat' using 3:5 t  'Average' w lines, 'gravitationuniv.dat' using 3:6 t 'StdDev' w lines
