set terminal png truecolor
set output "sincos.png"
set autoscale
set grid
set title "sin(x)_cos(x)"
set xrange [-pi:pi]
plot sin(x)
replot cos(x) with points pointtype 2
