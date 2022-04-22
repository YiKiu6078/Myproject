#include <iostream>
using namespace std;

class TestA
{
    private:
        int m_a;
    public:
        void show()
        {
            cout<<"this is TestA"<<endl;
        }
};

class TestB:public TestA
{
    private:
        int m_a;
    public:
        void show()
        {
            cout<<"this is TestB"<<endl;
        }
};

int main(int argc, char const *argv[])
{
    TestB tb;
    cout<<sizeof(tb)<<endl;
    tb.show();
    tb.TestA::show();
    return 0;
}

