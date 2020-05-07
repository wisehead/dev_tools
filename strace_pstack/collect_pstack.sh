#############################################################
#   File Name: a.sh
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/05/07-15:17:09
#############################################################
#!/bin/sh 
for i in {1..100}
    do
        echo $i
        #head -n $var $1|tail -1 >>error.wrong.sql
        sh pstack.sh 24029 >$i.txt
        sleep 30
        #sleep 10
    done
