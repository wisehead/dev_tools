set term post eps color solid enh
set output 'a.eps'
plot sin(x) 
replot cos(x)
