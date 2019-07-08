/*******************************************************************************
 *      File Name: a.cpp                                               
 *         Author: Hui Chen. (c) 2017                             
 *           Mail: chenhui13@baidu.com                                        
 *   Created Time: 2017/09/12-11:30                                    
 * Modified Time: 2017/09/12-11:30                                    
 *******************************************************************************/
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int size = nums.size();
        if (size < 2)
            return ret_vec;
        for (int i=size - 1; i>=1; i--)
        {
            for (int j=i-1; j>=0; j--)
            {
                if (nums[j] + nums[i] == target)
                {
                    ret_vec.push_back(j);
                    ret_vec.push_back(i);
                    cout<<"index:"<<ret_vec[0]<<","<<ret_vec[1]<<endl;
                    return ret_vec;
                }
            }
        }
        if (ret_vec.size() == 0)
        {
            cout<<"no results."<<endl;
        }
        return ret_vec;
    }
private:
    vector<int> ret_vec;
};

int main(int argc, char* argv[])
{
    vector<int> input_vec;
    vector<int> ret_vec;
    input_vec.push_back(2);
    input_vec.push_back(4);
    input_vec.push_back(6);
    input_vec.push_back(8);
    input_vec.push_back(10);
    cout<<"size of input_vec:"<<input_vec.size()<<endl;
    for (int i=0; i< input_vec.size(); i++)
    {
        cout<<"the "<<i<<" elements is:"<<input_vec[i]<<endl;
    }
    int target = 12;
    Solution solution;
    ret_vec = solution.twoSum(input_vec, target);
    return 0;
}
