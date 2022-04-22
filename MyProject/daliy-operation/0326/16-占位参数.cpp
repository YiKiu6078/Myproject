#include <iostream>
using namespace std;

struct A
{
    unsigned int a:10;
    unsigned int  :22;
    unsigned int c:2;
};

void Add(int a,int b,int = 0)
{
    cout<<a + b<<endl;
}

int main(int argc, char const *argv[])
{
    Add(1,2);
    cout<<sizeof(A)<<endl;
    return 0;
}
