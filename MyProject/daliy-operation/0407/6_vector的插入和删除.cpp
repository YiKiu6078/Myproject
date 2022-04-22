#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int main(int argc, char const *argv[])
{
    const char *str = "this is";
    const char *s = "nihao";
    vector<char> v1(s,s + strlen(s));
/*
    v1.resize(10);
    for(int i = 0;i < 10;i++)
    {
        v1[i] = i;
    }
    for(int i = 0;i < v.size();i++)
    {
        cout << v.at(i) << " ";
    }
    cout<<endl;
*/
    for (vector<char>::iterator it = v1.begin(); it != v1.end();it++)
    {
        cout << *it << " ";
    }
    cout<<endl;

    for (vector<char>::reverse_iterator rit = v1.rbegin(); rit != v1.rend();rit++)
    {
        cout << *rit << " ";
    }
    cout<<endl;

    for (vector<char>::const_iterator cit = v1.begin(); cit != v1.end();cit++)
    {
        cout << *cit << " ";
    }
    cout<<endl;
    return 0;
}
