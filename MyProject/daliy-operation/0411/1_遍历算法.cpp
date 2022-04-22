#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void show(int a)
{
    cout<<a<<endl;
}

class print
{
public:
    void operator()(int a)
    {
        cout<<a<<endl;
    }
};

int main(int argc, char const *argv[])
{
    int arr[5] = {1,2,3,4,5};
    vector<int> v(arr,arr+5);
//  for_each(v.begin(),v.end(),show);
    for_each(v.begin(),v.end(),print());//以函数对象形式遍历
    return 0;
}
