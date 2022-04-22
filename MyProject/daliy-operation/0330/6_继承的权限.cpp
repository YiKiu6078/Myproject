#include <iostream>
using namespace std;

class TestA
{
    private:
        int m_a;
    protected:
        int m_b;
    public:
        int m_c;
        void GetVal()
        {
            m_a = 1;
        }
};

class TestB:private TestA
{
    private:
        //int m_a;
    private:
        int m_b;
    private:
        int m_c;
    public:
        void show()
        {
           //m_a++;
            m_b++;
            m_c++;
        }
};

class TestC:protected TestA
{
    private:
      //  int m_a;
    protected:
        int m_b;
    protected:
        int m_c;
    public:
        void show()
        {
          //  m_a++;
            m_b++;
            m_c++;
        }
};

class TestD:public TestA
{
    private:
      //  int m_a;
    protected:
        int m_b;
    public:
        int m_c;
    public:
        void show()
        {
          //  m_a++;
            m_b++;
            m_c++;
        }
};

int main(int argc, char const *argv[])
{
    TestB t1;
    t1.show();

    TestC t2;
    t2.show();

    TestD t3;
    t3.show();
    return 0;
}
