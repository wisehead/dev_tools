set terminal png truecolor
set output "data.png"
set autoscale
set grid
set title "sin(x)"
plot sin(x), '1.dat'
