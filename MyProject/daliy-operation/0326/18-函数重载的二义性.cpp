#include <iostream>
using namespace std;

void Add(int a,int b)
{
    cout<<a + b<<endl;
}

void Add(int a,int b,int c = 1)
{
    cout<<a + b + c<<endl;
}

int main(int argc, char const *argv[])
{
    Add(1,3);
    return 0;
}
