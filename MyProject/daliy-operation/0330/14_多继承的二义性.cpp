#include <iostream>
using namespace std;

class BaseA
{
    public:
        int m_a;
};

class BaseB:public BaseA
{
    public:
        int m_b;
};

class BaseC:public BaseA
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
    BaseD d;
    cout<<sizeof(d)<<endl;
    return 0;
}
