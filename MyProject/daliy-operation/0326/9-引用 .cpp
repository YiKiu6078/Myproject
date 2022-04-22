#include <iostream>
using namespace std;

void test(int &a,int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

int main(int argc, char const *argv[])
{
    int a = 10,b = 20;
    cout<<"a = "<<a<<"b = "<<b<<endl;
    test(a,b);
    cout<<"a = "<<a<<"b = "<<b<<endl;
    int &c = b;
    c = 888;
    cout<<"b = "<<b<<endl; 
    return 0;
}
