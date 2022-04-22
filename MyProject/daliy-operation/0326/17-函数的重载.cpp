#include <iostream>
using namespace std;

void Swap(int &a,double &b)
{
    cout<<"第一个"<<endl;
    int tmp = a;
    a = b;
    b = tmp;
}

void Swap(int &a,int &b)
{
    cout<<"第二个"<<endl;
    int tmp = a;
    a = b;
    b = tmp;
}

void Swap(int &a,double &b,int c)
{
    cout<<"第三个"<<endl;
    int tmp = a;
    a = b;
    b = tmp;
}

void Swap(double &b,int &a)
{
    cout<<"第四个"<<endl;
    int tmp = a;
    a = b;
    b = tmp;
}

int main(int argc, char const *argv[])
{
    int a = 1,c = 2;
    double b = 1.111;
    Swap(b,c);
    return 0;
}
