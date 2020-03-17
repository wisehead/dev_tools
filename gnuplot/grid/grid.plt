set terminal png truecolor
set output "a.png"
set title "My first graph"
set xrange [-pi:pi]# we want only one cycle
set xtics ('0' 0, '90' pi/2, '-90' -pi/2, '45' pi/4,'-45' -pi/4,'135' 3*pi/4,'-135' -3*pi/4)
set grid
set xlabel 'Angle, in degrees'
set ylabel 'sin(angle)'
plot sin(x) 
