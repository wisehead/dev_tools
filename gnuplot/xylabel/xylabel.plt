set terminal png truecolor
set output "xy.png"
set title 'My first graph'
set xlabel 'Angle, in degrees'
set ylabel 'sin(angle)'
plot sin(x)
