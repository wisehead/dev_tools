/*******************************************************************************
 *      File Name: example2.c                                               
 *         Author: Hui Chen. (c) 2020                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2020/05/08-20:54                                    
 *	Modified Time: 2020/05/08-20:54                                    
 *******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
int a(void)
{
  sleep(1);               /*调用系统函数进行sleep*/
  return 0;
}
int b(void)
{
  sleep(4);               /*调用系统函数进行sleep*/
  return 0;
}
int main(int argc, char** argv)
{
   int iterations;
   if(argc != 2)
   {
      printf("Usage %s \n", argv[0]);
      exit(-1);
   }
   else
      iterations = atoi(argv[1]);
   printf("No of iterations = %d\n", iterations);
   while(iterations--)
   {
      a();
      b();
   }
}
