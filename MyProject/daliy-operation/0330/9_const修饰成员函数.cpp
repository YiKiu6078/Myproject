#include <iostream>
#include <cstring>
using namespace std;

class Student
{
    private:
        int m_id;
        char *m_name;
        int m_age;
    public:
        Student(int id,char *name,int age);
        void show();
        char * GetName()const;
        int GetId()const;
        int GetAge()const;
};

void Student::show()
{
    cout<<"m_name = "<<m_name<<"m_age = "<<m_age<<"m_id = "<<m_id<<endl;
}

char * Student::GetName()const
{
    return m_name;
}
int Student::GetId()const
{
    return m_id;
}
int Student::GetAge()const
{
    return m_age;
}
Student::Student(int id,char *name,int age):m_id(id),m_name(name),m_age(age)
{

}
int main(int argc, char const *argv[])
{
    Student s1(100,"what's up",19);
    s1.show();
    return 0;
}
