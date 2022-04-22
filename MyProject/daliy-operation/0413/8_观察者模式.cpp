#include <iostream>
#include <list>
#include <cstring>
using namespace std;

class Inform;
class Observer
{
public:
    virtual void Subscribe(Inform *l) = 0;
    virtual void UnSubscribe(Inform *l) = 0;
    virtual void Update(string str) = 0;
};

class Inform
{
public:
    virtual void Add(Observer *o) = 0;
    virtual void Remove(Observer *o) = 0;
    virtual void Notify(string str) = 0;
};

class Secreatary:public Inform
{
private:
    list<Observer *> l;
public:
    void Add(Observer* o)
    {
        l.push_back(o);
    }
    void Remove(Observer* o)
    {
        l.remove(o);
    }
    void Notify(string str)  //通知  遍历
    {
        for(list<Observer *>::iterator it = l.begin();it != l.end();it++)
        {
            (*it)->Update(str);
        }
    }
};

class Staff:public Observer
{
public:
    virtual void Subscribe(Inform *l)
    {
        l->Add(this);
    }
    void UnSubscribe(Inform *l)
    {

        l->Remove(this);
    }
    void Update(string str)
    {
        if(str == "WARNING")
        {
            cout<<"boss is comming"<<endl;
        }
        else
        {
            cout<<"Continue to play game"<<endl;
        }
    }
};

int main(int argc, char const *argv[])
{
    Inform *l = new Secreatary;
    Observer *o1 = new Staff;
    Observer *o2 = new Staff;
    Observer *o3 = new Staff;
    o1->Subscribe(l);
    o2->Subscribe(l);
    o3->Subscribe(l);
    l->Remove(o1);
    l->Notify("WARNING");
    return 0;
}
