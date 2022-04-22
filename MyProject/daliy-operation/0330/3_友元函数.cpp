#include <iostream>
using namespace std;

class Test
{
    friend void Show(Test &t);
    private:
        int m_a;
    public:
        Test()
        {
            m_a = 100;
        }
        void show()
        {
            cout<<"m_a = "<<m_a<<endl;
        }
};

void Show(Test &t)
{
    cout<<"m_a = "<<t.m_a<<endl;
}

int main(int argc, char const *argv[])
{
    Test t1;
    t1.show();
    Show(t1);
    return 0;
}
