set terminal png truecolor
set output "sincos2.png"
set autoscale
set grid
set title "sin(x)_cos(x)"
plot [-pi:pi] sin(x), cos(x) with points pointtype 2
