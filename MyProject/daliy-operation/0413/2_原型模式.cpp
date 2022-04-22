#include <iostream>
#include <cstring>
using namespace std;

class Person
{
protected:
    string m_name;
    int m_age;
public:
    Person(){}
    Person(string n,int a)
    {
        m_name = n;
        m_age = a;
    }
    virtual void show() = 0;
    virtual Person*Clone() = 0;
};

class Student:public Person
{
private:
    int id;
public:
    Student(){}
    Student(string n,int a,int i):Person(n,a)
    {
        id = i;
    }
    void show()
    {
        cout<<m_name<<" "<<m_age<<" "<<id<<" "<<endl;
    }
    Person * Clone()
    {
        Student *stu = new Student;
        *stu = *this;
        return stu;
    }
};

int main(int argc, char const *argv[])
{
    Person *p = new Student("liu",18,01);
    Person *p1 = p->Clone();
    p->show();
    p1->show();
    return 0;
}
