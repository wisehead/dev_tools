#############################################################
#   File Name: run.sh
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/05/26-10:05:21
#############################################################
#!/bin/sh 
#attach mysqld process
strace -o output.txt -T -tt -e trace=all -p 22981
#init a process.
strace -f -F -o ~/straceout.txt ./mysqld
