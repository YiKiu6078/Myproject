#include <iostream>
using namespace std;

class System
{
public:
    virtual void fun() = 0;
};

class SystemA:public System
{
public:
    virtual void fun()
    {
        cout<<"systemA"<<endl;
    }
};

class SystemB:public System
{
public:
    virtual void fun()
    {
        cout<<"systemB"<<endl;
    }
};

class SystemC:public System
{
public:
    virtual void fun()
    {
        cout<<"systemC"<<endl;
    }
};

class Facade
{
private:
    SystemA *a;
    SystemB *b;
    SystemC *c;
public:
    Facade()
    {
        a = new SystemA;
        b = new SystemB;
        c = new SystemC;
    }
    ~Facade()
    {
        delete a;
        delete b;
        delete c;
    }
    void fun()
    {
        a->fun();
        b->fun();
        c->fun();
    }
};

int main(int argc, char const *argv[])
{
    Facade *f = new Facade;
    f->fun();
    return 0;
}
