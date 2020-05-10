#############################################################
#   File Name: run.sh
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/05/10-22:21:59
#############################################################
#!/bin/sh 
perf timechart record ./a.out 5000
perf timechart
perf record -e cpu-clock ./a.out 5000
perf report
perf record -g -e cpu-clock ./a.out 5000
perf report
perf stat ./a.out 5000
perf report

