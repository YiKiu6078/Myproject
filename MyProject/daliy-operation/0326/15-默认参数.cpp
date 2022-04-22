#include <iostream>
using namespace std;

int Add(int a = 3,int b = 6,int c = 0)
{
    return a + b;
}

int main(int argc, char const *argv[])
{
    cout<<Add()<<endl;
    return 0;
}
