#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


bool GreaterTwo(int a)
{
    return a > 2;
}

class GteaterThree
{
public:
    bool operator()(int a)
    {
        return a > 3;
    }
};

int main(int argc, char const *argv[])
{
    int arr[6] = {1,2,3,5,5,6};
    vector<int> v(arr,arr+6);
    vector<int>::iterator it = adjacent_find(v.begin(),v.end()); //查找相邻的相同元素
    if (v.end() == it)
    {
        cout<<"不存在重复且相邻的元素"<<endl;
    }
    {
        cout<<*it<<endl;
    }
    bool ret = binary_search(v.begin(),v.end(),5);//判断元素5是否存在
    if (ret)
    {
        cout<<"元素存在"<<endl;
    }
    else
    {
        cout<<"元素不存在"<<endl;
    }
    int num = count(v.begin(),v.end(),5);
    cout<<"num = "<<num<<endl;
    num = count_if(v.begin(),v.end(),GreaterTwo);//GreaterTwo为回调函数；num 是个数；
    cout<<num<<endl;
    it = find(v.begin(),v.end(),0);
    if (it != v.end())
    {
        cout<<*it<<endl;
    }
    else
    {
        cout<<"元素不存在"<<endl;
    }

    it = find_if(v.begin(),v.end(),GteaterThree());
    if (it != v.end())
    {
        cout<<"大于3： "<<*it<<endl;
    }
    else
    {
        cout<<"元素不存在"<<endl;
    }

    return 0;
}
