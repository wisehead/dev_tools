/*******************************************************************************
 *      file name: hello.cpp                                               
 *         author: Hui Chen. (c) 2019                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 2019/07/08-16:19:54                              
 *  modified time: 2019/07/08-16:19:54                              
 *******************************************************************************/
/* hello.cpp */
#include <iostream>
using namespace std;
int main()
{
    cout << "Please enter your name: ";
	string name;
    cin >> name;
    cout << "Hello, " << name;
    cout << "\n";
	return 0;
}
