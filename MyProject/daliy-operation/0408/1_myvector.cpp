#include <iostream>
#include <vector>
#include <algorithm>  //标准算法头文件
using namespace std;

void myPrint(int val)
{
    cout<<val<<endl;
}

int main(int argc, char const *argv[])
{
    vector<int> v;
 
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);

    //使用迭代器
    vector<int>::iterator itBegin = v.begin();
    vector<int>::iterator itEnd = v.end();

    while(itBegin != itEnd)
    {
        cout<<*itBegin<<" ";
        itBegin++;
    }
    cout<<endl;


    for(vector<int>::iterator it = v.begin();it != v.end();it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;

    //使用STL算法进行遍历输出
    for_each(v.begin(),v.end(),myPrint);  //第三参数为回调函数
    return 0;
}
