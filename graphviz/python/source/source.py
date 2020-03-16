#############################################################
#   File Name: source.py
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/03/16-20:47:55
#############################################################
#!/usr/bin/env python 
#-*- coding:utf8 -*-

from graphviz import Source
code2="""graph
graphname{
rankdir=LR;  //Rank Direction Left to Right
a[label="node1"];
a -- node2;
}"""
t=Source(code2)
t.view()
