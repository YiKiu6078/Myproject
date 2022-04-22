#include <iostream>
#include <cstring>
using namespace std;

class Preson
{

    protected:
        char m_name[32];
        int m_age;
    public:
        Preson()
        {
            strcpy(m_name,"what's up");
            m_age = 20;
        }
};

class Student:public Preson
{
    private:
        int id;
    public:
        Student(int id)
        {
            this->id = id;
        }
        void show()
        {
            cout<<"m_name = "<<m_name<<" m_age = "<<m_age<<" id = "<<id<<endl;
        }
};

int main(int argc, char const *argv[])
{
    Student s1(101);
    s1.show();
    return 0;
}
