#include <iostream>
using namespace std;

class Complex
{
    private:
        int m_a;
        int m_b;
    public:
        Complex(int a,int b)
        {
            this->m_a = a;
            this->m_b = b;
        }
        void print()
        {
            cout<<m_a<<"+"<<m_b<<"i"<<endl;
        }
        Complex operator+(const Complex &c)
        {
            Complex t(0,0);
            t.m_a = this->m_a + c.m_a;
            t.m_b = this->m_b + c.m_b;
            return t;
        }
};

int main(int argc, char const *argv[])
{
    Complex c1(1,2);
    Complex c2(2,3);
    c1.print();
    Complex t(0,0);

    t = c1 + c2;

    t.print();
    return 0;
}
