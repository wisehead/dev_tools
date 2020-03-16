#############################################################
#   File Name: color.py
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/03/16-21:21:49
#############################################################
#!/usr/bin/env python 
#-*- coding:utf8 -*-

from graphviz import Digraph

g = Digraph('测试图片')
g.node(name='a',color='red')
g.node(name='b',color='blue')
g.edge('a','b',color='green')
g.view()
