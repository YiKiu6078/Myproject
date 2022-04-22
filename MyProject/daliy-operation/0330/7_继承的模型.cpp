#include <iostream>
using namespace std;

class Person
{
    public:
        int m_age;
};

class Student:public Person
{
    public:
        int m_id;
};

int main(int argc, char const *argv[])
{
    Student s1;
    cout<<sizeof(Person)<<endl;
    cout<<sizeof(s1)<<endl;
    cout<<&s1<<endl;
    cout<<&s1.m_age<<endl;
    cout<<&s1.m_id<<endl;
    return 0;
}
