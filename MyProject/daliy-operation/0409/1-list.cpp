#include <iostream>
#include <cstring>
#include <list>
using namespace std;

class Student
{
private:
    int id;
    string name;
public:
    Student(){}
    Student(int i,string n);
    void show();
    bool operator==(const Student& s);
};

Student::Student(int i,string n)
{
    id = i;
    name = n;
}

void Student::show()
{
    cout<<"id = "<<id<<" name = "<<name<<endl;
}

bool Student::operator==(const Student& s)
{
    if(this->id == s.id && this->name == s.name)
    {
        return true;
    }
    else
    {
        return false;
    }
//    return false;
}

int main(int argc, char const *argv[])
{
    Student s1(1,"H");
    Student s2(2,"e");
    Student s3(3,"l");
    Student s4(4,"l");
    Student s5(5,"o");

    list<Student> l;
    l.push_back(s1);
    l.push_back(s2);
    l.push_back(s3);
 //   l.push_back(s4);
 //   l.push_back(s5);
    l.push_front(s4);
    l.push_front(s5);

    for(list<Student>::iterator it = l.begin();it != l.end();it++)
    {
        it->show();
    }
    cout<<"*****************"<<endl;
    l.pop_back();
    l.pop_front();
    for(list<Student>::iterator it = l.begin();it != l.end();it++)
    {
        it->show();
    }
    cout<<"第一个元素为："<<endl;
    l.front().show();
    cout<<"第二个元素为: "<<endl;
    l.back().show();
    cout<<"*****************"<<endl;
    l.resize(8,s1);
    for(list<Student>::iterator it = l.begin();it != l.end();it++)
    {
        it->show();
    }
    cout<<"*****************"<<endl;

    Student s[5] = {Student{6,"w"},Student{7,"h"},Student{8,"a"},Student{9,"t"},Student{10,"'"}};
    l.insert(l.begin(),s[0]);
    l.insert(l.end(),s[4]);
    for(list<Student>::iterator it = l.begin();it != l.end();it++)
    {
        it->show();
    }
    cout<<"链表的大小为："<<l.size()<<endl;

    cout<<"在链表尾部插入一个区间"<<endl;
    l.insert(l.end(),s,s + 3);//结构体数组首元素到第三区间都插入；
    for(list<Student>::iterator it = l.begin();it != l.end();it++)
    {
        it->show();
    }

    cout<<"删除一个区间"<<endl;
    list<Student>::iterator it = l.begin();
    for(int i = 0;i < 5;i++)
    {
        it++;
    }
    l.erase(it,l.end());//从第六个开始（包含第六个）到最后，中间元素全部删除；
    for(list<Student>::iterator it = l.begin();it != l.end();it++)
    {
        it->show();
    }
    cout<<"删除第一个"<<endl;
    l.erase(l.begin());
    for(list<Student>::iterator it = l.begin();it != l.end();it++)
    {
        it->show();
    }

    cout<<"删除一个具体元素"<<endl; //需要重载==
    l.remove(s2);
    for(list<Student>::iterator it = l.begin();it != l.end();it++)
    {
        it->show();
    }

    cout<<"链表反转"<<endl;
    l.reverse();
    for(list<Student>::iterator it = l.begin();it != l.end();it++)
    {
        it->show();
    }
    return 0;
}
