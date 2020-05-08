/*******************************************************************************
 *      File Name: test.c                                               
 *         Author: Hui Chen. (c) 2020                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2020/05/08-21:11                                    
 *	Modified Time: 2020/05/08-21:11                                    
 *******************************************************************************/
#include <stdio.h>
void a()
{
  printf("\t\t+---call a() function\n");
}

void c()
{
  printf("\t\t+---call c() function\n");
}

int b()
{
    printf("\t+--- call b()     function\n");
    a();
    c();
    return 0;
}

int main()
{
  printf(" main() function()\n");
  b();
  return 0;
}
