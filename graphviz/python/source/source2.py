#############################################################
#   File Name: 2.py
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/03/16-21:14:17
#############################################################
#!/usr/bin/env python 
#-*- coding:utf8 -*-
from graphviz import Source

src = Source('digraph "the holy hand grenade" { rankdir=LR; 1 -> 2 -> 3 -> lob }')

src.view()
