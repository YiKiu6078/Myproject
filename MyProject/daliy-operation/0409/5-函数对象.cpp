#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

class Student
{
    friend class Compare;
private:
    int id;
    string name;
public:
    Student(int i,string n)
    {
        id = i;
        name = n;
    }
    void show()const
    {
        cout<<"id = "<<id<<"name = "<<name<<endl;
    }
    bool operator<(const Student & s)const
    {
        return this->id > s.id;
    }
};

class Compare
{
public:
    bool operator()(const Student & s1,const Student & s2)const
    {
        return s1.id > s2.id;
    }
};

int main(int argc, char const *argv[])
{
    Student s1(1,"w");
    Student s2(2,"h");
    Student s3(3,"a");
    Student s4(4,"t");
    Student s5(5,"'");
    Student s6(6,"s");
    Student s7(7," ");
    Student s8(8,"u");
    Student s9(9,"p");

 //   priority_queue<Student> p;
    priority_queue<Student,vector<Student>,Compare> p;
    p.push(s1);
    p.push(s2);
    p.push(s3);
    p.push(s4);
    p.push(s5);
    p.push(s6);
    p.push(s7);
    p.push(s8);
    p.push(s9);
    while (!p.empty())
    {
        p.top().show();
        p.pop();
    }
    Compare c;
    cout<<c(s1,s2)<<endl;
    return 0;
}
