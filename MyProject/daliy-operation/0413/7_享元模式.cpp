#include <iostream>
#include <map>
using namespace std;

class Student
{
private:
    int id;
    string name;
    int age;
public:
    Student(){}
    Student(string n,int i,int a)
    {
        name = n;
        id = i;
        age = a;
    }
    string GetName()
    {
        return name;
    }
    int GetId()
    {
        return id;
    }
    int GetAge()
    {
        return age;
    }
};

class FwFactory
{
private:
    multimap<int,Student*> *m;
public:
    FwFactory()
    {
        m = new multimap<int,Student*>;
    }
    ~FwFactory()
    {
        while (!m->empty())
        {
            Student* tmp = m->begin()->second;
            delete m;
            m->erase(m->begin());
        }
        delete m;
    }
    void GetPerson(int id)
    {
        string name;
        int age;
        multimap<int,Student*>::iterator it;
        it = m->find(id);
        if (it == m->end())
        {
            cout<<"please input name and id"<<endl;
            cin>>name>>age;
            Student *stu = new Student(name,id,age);
            m->insert(make_pair(id,stu));
        }
        else
        {
            Student *stu = it->second;
            cout<<stu->GetName()<<" "<<stu->GetId()<<" "<<stu->GetAge()<<" "<<endl;
        }
    }
};

int main(int argc, char const *argv[])
{
    FwFactory * f = new FwFactory;
    f->GetPerson(1);
    f->GetPerson(2);
    f->GetPerson(3);
    f->GetPerson(4);

    cout<<"-----------------"<<endl;
    f->GetPerson(3);
    return 0;
}
