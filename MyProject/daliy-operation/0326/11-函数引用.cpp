#include <iostream>
using namespace std;


int a = 100;

int &fun()
{
    int x = 1;
    return a;
}

int main(int argc, char const *argv[])
{
    fun();
    int c = fun();
    cout<<"c = "<<c<<endl;
    int &b = fun();
    b = 10000;
    cout<<"a = "<<a<<endl;
    fun() = 200;
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    return 0;
}
