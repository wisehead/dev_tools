/*******************************************************************************
 *      file name: test.cpp                                               
 *         author: Hui Chen. (c) 2020                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2020/04/04-21:40:37                              
 *  modified time: 2020/04/04-21:40:37                              
 *******************************************************************************/
#include <iostream>
using namespace std;

int my_add(int a, int b)
{
	return a + b;
}

int main()
{
	int x = 2, y = 3;
	int ret = my_add(x, y);
}
