#include <iostream>
using namespace std;

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

/*    Complex operator++()
    {
        this->m_a++;
        this->m_b++;
        return *this;
    }*/
    Complex operator++(int)  //int 为占位参数为了区分前置++和后置++
    {
        this->m_a++;
        this->m_b++;
        return *this;
    }
};

ostream &operator<<(ostream &out,Complex &c1)  //只可以定义成全局的
{
    out<<c1.m_a<<"+"<<c1.m_b<<"i";
    return out;
}

int main(int argc, char const *argv[])
{
    Complex c1(1,1);
    Complex c2(2,1);
    c1.print();
    Complex t(0,0);
    
    t = c1 + c2;
//    t.print();

 //   t = ++c1;
    t = c2++;
    cout << t << endl;
    return 0;
}


