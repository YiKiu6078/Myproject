#include <iostream>
using namespace std;

class Complex
{
    friend Complex operator+(const Complex &c1,const Complex &c2);
private:
    int m_a;
    int m_b;
public:
    Complex(int a,int b)
    {
        m_a = a;
        m_b = b;
    }
    void print()
    {
        cout<<m_a<<"+"<<m_b<<endl;
    }
/*    Complex operator+(const Complex & c2)
    {
        Complex t(0,0);
        t.m_a = this->m_a + c2.m_a;
        t.m_b = this->m_b + c2.m_b;
        return t;
    }*/
};

Complex operator+(const Complex &c1,const Complex &c2)
{
    Complex t(0,0);
    t.m_a = c1.m_a + c2.m_a;
    t.m_b = c1.m_b + c2.m_b;
    return t;
}

int main(int argc, char const *argv[])
{
    Complex c1(1,1);
    Complex c2(2,1);
    c1.print();
    Complex t(0,0);
    
    t = c1 + c2;
    t.print();
    return 0;
}
