#include <iostream>
using namespace std;

class Date
{
    private:
        int m_year;
        int m_month;
        int m_day;
    public:
        Date(int y,int m,int d)
        {
            cout<<"Datec的有参构造函数"<<endl;
            m_year = y;
            m_month = m;
            m_day = d;
        }
};

class Student
{
    private:
        const int id;
        Date brith;
    public:
        Student(int i,int y,int m,int d):brith(y,m,d),id(i)
        {
            cout<<"Student的有参构造函数"<<endl;
        }
};

int main(int argc, char const *argv[])
{
    Student s1(101,1997,10,10);
    return 0;
}
