/*******************************************************************************
 *      file name: test.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/04/04-21:59:23                              
 *  modified time: 2020/04/04-21:59:23                              
 *******************************************************************************/
#include<stdio.h>
int divide(int x, int y)
{
    return x/y;
}

int main()
{
    printf("hello world\n");
    int x = 3;
    int y = 0;
    int div = divide(x, y); 
    printf("%d / %d = %d\n", x, y, div);
    return 0;
}
