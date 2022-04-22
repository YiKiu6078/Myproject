#include <iostream>
#include <set>
using namespace std;

class Student
{
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
        return this->id < s.id;
    }
    bool operator>(const Student & s)const
    {
        return this->id > s.id;
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

 //   set<Student> s;
    set<Student,greater<Student>> s;
    s.insert(s1);
    s.insert(s2);
    s.insert(s3);
    s.insert(s4);
    s.insert(s5);
    s.insert(s6);
    s.insert(s7);
    s.insert(s8);
    s.insert(s9);
    for(set<Student>::iterator it = s.begin();it != s.end();it++)
    {
        it->show();
    }

    cout<<"set集合的大小"<<s.size()<<endl;
    cout<<"set的删除"<<endl;
    s.erase(--s.end(),s.end());
    for(set<Student>::iterator it = s.begin();it != s.end();it++)
    {
        it->show();
    }
    cout<<"set的查找"<<endl;
    set<Student,greater<Student>>::iterator it = s.find(s5);
    if (it == s.end())
    {
        cout<<"对象不存在";
    }
    else
    {
        it->show();
    }

    cout<<"low_bount"<<endl;
    Student ss(1,"!");
    it = s.lower_bound(ss);
    if (it == s.end())
    {
        cout<<"对象不存在"<<endl;
    }
    else
    {
        it->show();
    }

    cout<<"upper_bount"<<endl;
    it = s.upper_bound(ss);
    if (it == s.end())
    {
        cout<<"对象不存在"<<endl;
    }
    else
    {
        it->show();
    }

    cout<<"equal_range"<<endl;
    pair<set<Student,greater<Student>>::iterator,set<Student,greater<Student>>::iterator>p;
    p = s.equal_range(s3);
    p.first->show();
    p.second->show();
    return 0;
}
