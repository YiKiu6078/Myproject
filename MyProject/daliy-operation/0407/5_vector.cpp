#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    int data[10] = {1,2,3,4,5,6,7,8,9,10};
    vector<int> v1;
    vector<int> v2(data,data + 10);
    vector<int> v3(10,1);

    v1.resize(10);
    for(int i = 0;i < 10;i++)
    {
        v1[i] = i;
    }
    for(int i = 0;i < v2.size();i++)
    {
        cout << v2.at(i) << " ";
    }
    cout<<endl;

    for (vector<int>::iterator it = v2.begin(); it != v2.end();it++)
    {
        cout << *it << " ";
    }
    cout<<endl;

    for (vector<int>::reverse_iterator rit = v2.rbegin(); rit != v2.rend();rit++)
    {
        cout << *rit << " ";
    }
    cout<<endl;

    for (vector<int>::const_iterator cit = v2.begin(); cit != v2.end();cit++)
    {
        cout << *cit << " ";
    }
    cout<<endl;
    return 0;
}
