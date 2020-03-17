set terminal png truecolor
set output "a.png"
set title "My first graph"
set xtics ('0' 0, '90' pi/2, '-90' -pi/2, '45' pi/4,'-45' -pi/4,'135' 3*pi/4,'-135' -3*pi/4)
set grid
set xlabel 'Angle, in degrees'
set ylabel 'sin(angle)'
set key top left
set key box
plot [-pi:pi] sin(x) title 'sinusoid' with linespoints pointtype 5, cos(x) t 'cosine' w boxes lt 4
