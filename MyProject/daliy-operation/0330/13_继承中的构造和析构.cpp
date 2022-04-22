#include <iostream>
using namespace std;

class BaseA
{
    protected:
        int m_a;
        int m_b;
    public:
        BaseA(int a,int b);
        ~BaseA();
};

BaseA::BaseA(int a,int b):m_a(a),m_b(b)
{
    cout<<"BaseA构造函数被调用"<<endl;
}

BaseA::~BaseA()
{
    cout<<"BaseA的析构函数"<<endl;
}

class BaseB
{
    protected:
        int m_c;
        int m_d;
    public:
        BaseB(int c,int d);
        ~BaseB();
};

BaseB::BaseB(int c,int d):m_c(c),m_d(d)
{
    cout<<"BaseB构造函数被调用"<<endl;
}

BaseB::~BaseB()
{
    cout<<"BaseB的析构函数"<<endl;
}

class Deived:public BaseA,public BaseB
{
private:
    int m_e;
public:
    Deived(int a,int b,int c,int d,int e);
    ~Deived();
    void show()
    {
        cout<<m_a<<","<<m_b<<","<<m_c<<","<<m_d<<","<<m_e<<endl;
    }
};

Deived::Deived(int a,int b,int c,int d,int e):BaseA(a,b),BaseB(c,d),m_e(e)
{
    cout<<"Deived的有参构造函数"<<endl;
}

Deived::~Deived()
{
    cout<<"Deived的析构函数被调用"<<endl;
}


int main(int argc, char const *argv[])
{
    Deived d1(1,2,3,4,5);
    d1.show();
    return 0;
}
