/*******************************************************************************
 *      file name: main.c                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/07/08-17:03:16                              
 *  modified time: 2019/07/08-17:03:16                              
 *******************************************************************************/
#include <stdio.h>
int main(){
    int a=4;
    int b=6;
    int array[3];
    array[0]=1;
    array[1]=10;
    array[2]=100;
    int *p;
    p=&a;
    int i=0;
    while(i<6){
        printf("*p=%d\n",*p);
        p++;
        i++;
    }
    return 0;
}
