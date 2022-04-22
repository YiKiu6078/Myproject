#include <iostream>
using namespace std;

int f1()
{
    cout<<"this is f1"<<endl;
    return 0;
}

int f2()
{
    cout<<"this is f2"<<endl;
    return 1;
}

class Complex
{   
    friend ostream &operator<<(ostream &out,Complex &c1);
    //friend Complex operator+(const Complex &c1,const Complex &c2);
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
    Complex operator+(const Complex & c2)
    {
        Complex t(0,0);
        t.m_a = this->m_a + c2.m_a;
        t.m_b = this->m_b + c2.m_b;
        return t;
    }

    bool operator&&(const Complex &c)
    {
        return (this->m_a && c.m_a) && (this->m_b && c.m_b);
    }
};

ostream &operator<<(ostream &out,Complex &c1)  //只可以定义成全局的
{
    out<<c1.m_a<<"+"<<c1.m_b<<"i";
    return out;
}

int main(int argc, char const *argv[])
{
    if (f1() && f2())  //短路原则，最终只会显示f1;
    {
        cout<<"what's up"<<endl;
    }
    Complex c1(1,1);
    Complex c2(2,1);
    Complex c3(0,0);
    
    if (c1 && (c2 + c3))
    {
        cout << "c1 && c2" << endl;
    }
    
    return 0;
}


