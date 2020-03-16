#############################################################
#   File Name: dg2.py
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/03/16-20:42:20
#############################################################
#!/usr/bin/env python 
#-*- coding:utf8 -*-

from graphviz import Digraph
dot=Digraph()
#因为Graph这个节点在后面和别的点连接的比较多，所以简写为g
#下面这句话实际是dot.node("g",label="Graph")
dot.node("g","Graph")
#不用简写的直接采用label来表示
dot.edge("Session","g")
dot.edge("g","Placeholder")
dot.edge("g","Variable")
dot.view()
