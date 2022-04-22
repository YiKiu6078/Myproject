#include <iostream>
#include <cstring>
using namespace std;

class Person
{
    protected:
        char m_name[32];
        int m_age;
    public:
        Person()
        {
            cout<<"Person的无参构造函数"<<endl;
            strcpy(m_name,"what's up");
            m_age = 19;
        }
        void SetVal(char *name,int age)
        {
            strcpy(m_name,name);
            m_age = age;
        }
        Person(const Person &p)
        {
            cout<<"person的拷贝构造"<<endl;
            strcpy(m_name,p.m_name);
            m_age = p.m_age;
        }
        void print()
        {
            cout<<"m_name = "<<m_name<<"m_age = "<<m_age<<endl;
        }
};

class Student:public Person
{
    private:
        int id;
    public:
        void SetId(int i)
        {
            id = i;
        }
        void show()
        {
            cout<<"m_name = "<<m_name<<"m_age = "<<m_age<<endl;
        }
};

int main(int argc, char const *argv[])
{
    Person p1;
    p1.SetVal("zhangsan",19);
    p1.print();

    Student s1;
    s1.SetVal("lisi",20);
    s1.SetId(200);
    s1.print();

    Student *ps = &s1;
    ps->show();

    Person *p = &s1;
    p->SetVal("what's up",66);
    p->print();

    Person &p2 = s1;
    p2.print();

    Person p3 = s1;
    p3.print();
    return 0;
}
