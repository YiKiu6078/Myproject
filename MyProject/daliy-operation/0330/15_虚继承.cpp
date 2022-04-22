#include <iostream>
using namespace std;

class BaseA
{
    public:
        int m_a;
};

class BaseB:virtual public BaseA
{
    public:
        int m_b;
};

class BaseC:virtual public BaseA
{
    public:
        int m_c;
};

class BaseD:public BaseB,public BaseC
{
    public:
        int m_d;
};

int main(int argc, char const *argv[])
{
    BaseB b;
    cout<<sizeof(b)<<endl;
    cout<<&b<<endl;
    cout<<&b.m_a<<endl;
    cout<<&b.m_b<<endl;
    cout<<"*****************"<<endl;
    BaseD d;
    cout<<sizeof(d)<<endl;
    cout<<&d<<endl;
    cout<<&d.m_a<<endl;
    cout<<&d.m_b<<endl;
    cout<<&d.m_c<<endl;
    cout<<&d.m_d<<endl;
    return 0;
}
