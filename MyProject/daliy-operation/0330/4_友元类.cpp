#include <iostream>
using namespace std;

class Test
{
    friend class Test2;
    private:
        int m_a;
    public:
        Test()
        {
            m_a = 100;
        }
        void show(Test t)
        {
            cout<<"m_a = "<<m_a<<endl;
        }
};

class Test2
{
    friend class Test;
    private:
        int m_b;
    public:
       
        Test2()
        {
            m_b = 200;
        }
        void print(Test &t)
        {
            cout<<"m_b = "<<m_b<<endl;
        }
};

int main(int argc, char const *argv[])
{
    Test t1;
    Test2 t2;
    t2.print(t1);
    return 0;
}