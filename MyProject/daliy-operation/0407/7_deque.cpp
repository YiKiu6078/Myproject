#include <iostream>
#include <deque>
using namespace std;

int main(int argc, char const *argv[])
{
    int data[10] = {2,3,1,4,6,5,8,9,5,5};
    deque<int> d(data,data + 10);
    for(deque<int>::iterator it = d.begin();it != d.end();)
    {
        if(*it == 5)
        {
            d.erase(it);
        }
        else
        {
            it++;
        }
    }
    for(deque<int>::iterator it = d.begin();it != d.end();it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
    return 0;
}
