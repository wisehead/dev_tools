#############################################################
#   File Name: redblue.py
#     Autohor: Hui Chen (c) 2020
#        Mail: chenhui13@baidu.com
# Create Time: 2020/03/16-22:01:38
#############################################################
#!/usr/bin/env python 
#-*- coding:utf8 -*-

from graphviz import Graph
#排列方式设定为环形
g=Graph(engine="circo")
#节点1为白色
g.node("1",shape="circle",color="white")
for i in range(2,8):
    #第二层节点为红色
    g.node("%d"%i,shape="circle",color="red")
    #第三层为默认颜色
    a=2*(i-2)+8
    b=2*(i-2)+9    
    g.node("%d"%a,shape="circle") 
    g.node("%d"%b,shape="circle") 
    #添加第二层到第三层的边
    g.edge("1","%d"%i)
    #添加第三层到第二层的边
    g.edge("%d"%a,"%d"%i)
    g.edge("%d"%b,"%d"%i)
#添加
g.node("last",shape="box")
g.node("tail",shape="box") 
g.edge("last","7")
g.edge("tail","17")
g.view()
