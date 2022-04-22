#include <iostream>
using namespace std;

class Student
{
    public:
        static int count;
    private:
        int id;
    public:
        Student()
        {
            count++;
            id = count;
        }
        static int GetCount()
        {
            return count;
        }
        int GetCount1()
        {
            return count;
        }
};
int Student::count = 0;

int main(int argc, char const *argv[])
{
    Student s1;
    Student s2;
//    cout<<"s1.count ="<<s1.count<<endl;
    cout<<"s2.count ="<<s2.count<<endl;
    cout<<"Student::count ="<<Student::count<<endl;
    cout<<"Student::GetCount() ="<<Student::GetCount()<<endl;
    cout<<"s1.GetCount1() ="<<s1.GetCount1()<<endl;
    return 0;
}
