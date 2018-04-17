/*******************************************************************************
 *      File Name: print_stack.cpp                                               
 *         Author: Hui Chen. (c) 2018                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2018/04/17-15:32                                    
 *	Modified Time: 2018/04/17-15:32                                    
 *******************************************************************************/
#include <iostream>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
 
void fun1();
void fun2();
void fun3();
 
void print_stacktrace();
 
int main()
{
    fun3();
}
 
void fun1()
{
    printf("stackstrace begin:\n");
    print_stacktrace();
}
 
void fun2()
{
    fun1();
}
 
void fun3()
{
    fun2();
}
 
void print_stacktrace()
{
    int size = 16;
    void * array[16];
    int stack_num = backtrace(array, size);
    char ** stacktrace = backtrace_symbols(array, stack_num);
    for (int i = 0; i < stack_num; ++i)
    {
        printf("%s\n", stacktrace[i]);
    }
    free(stacktrace);
}
