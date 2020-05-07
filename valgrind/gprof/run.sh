#############################################################
#   File Name: run.sh
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/05/07-22:01:54
#############################################################
#!/bin/sh 
valgrind  --tool=callgrind /ssd1/chenhui/dbpath/libexec/mysqld --defaults-file=$bpath/etc/my.cnf --user=root &
callgrind_annotate callgrind.out.20555 >out.txt
python3 gprof2dot.py -f callgrind callgrind.out.20555 >dot.txt
cat dot.txt | dot -Tpdf -o report.pdf
