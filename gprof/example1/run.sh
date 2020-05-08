#############################################################
#   File Name: run.sh
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/05/08-21:38:04
#############################################################
#!/bin/sh 
gcc -pg example1.c
./a.out 5000
gprof -b a.out gmon.out >prof.log
cat prof.log |python3 gprof2dot.py  >a.dot
cat a.dot|dot -Tpng -o output.png
