#include <iostream>
#include <cstring>
using namespace std;

class Preson
{
    protected:
        char m_name[32];
        int m_age;
    public:
        Preson(const char *name,int age)
        {
            cout<<"Person的构造函数"<<endl;
            strcpy(this->m_name,name);
            this->m_age = age;
        }
        ~Preson()
        {
            cout<<"Person的析构函数"<<endl;
        }
};

class Date
{
    private:
        int m_year;
        int m_month;
        int m_day;
    public:
    /*    Date(int y,int m,int d)
        {
            cout<<"Datec的有参构造函数"<<endl;
            m_year = y;
            m_month = m;
            m_day = d;
        }*/
        Date(int y,int m,int d)
        {
            cout<<"Date的有参构造"<<endl;
            m_year = y;
            m_month = m;
            m_day = d;
        }
        ~Date()
        {
            cout<<"Date的析构函数"<<endl;
        }
};

class Student:public Preson
{
    private:
        int id;
        Date brith;
    public:
        Student(int id):brith(2000,1,1),Preson("what's up",22)
        {
            cout<<"Student的构造函数"<<endl;
            this->id = id;
        }
        void show()
        {
            cout<<"m_name = "<<m_name<<" m_age = "<<m_age<<" id = "<<id<<endl;
        }
        ~Student()
        {
            cout<<"Student的析构函数"<<endl;
        }
};

int main(int argc, char const *argv[])
{
    Student S1(101);
    S1.show();
    return 0;
}
