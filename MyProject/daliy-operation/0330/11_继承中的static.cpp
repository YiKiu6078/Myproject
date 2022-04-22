#include <iostream>
using namespace std;

class Person
{
    public:
        static int count;
    Person()
    {
        this->count++;
    }
};

int Person::count = 0;
class Student:public Person
{

};

int main(int argc, char const *argv[])
{
    Student s1;
    Student s2;
    Person p1;
    Person p2;
    cout<<Person::count<<endl;
    cout<<Student::count<<endl;
    return 0;
}
