#include <iostream>
#include <cstring>
using namespace std;

class Furit
{
public:
    virtual void show() = 0;
};

class Apple:public Furit
{
public:
    void show()
    {
        cout<<"this is Apple"<<endl;
    }
};

class Banana:public Furit
{
public:
    void show()
    {
        cout<<"this is banana"<<endl;
    }
};

class Pear:public Furit
{
public:
    void show()
    {
        cout<<"this is Pear"<<endl;
    }
};

class FuritFactory
{
public:
    virtual Furit* CreateFurit() = 0;
};

class AppleFactory:public FuritFactory
{
public:
    Furit* CreateFurit()
    {
        return new Apple;
    }
};

class BananaFactory:public FuritFactory
{
public:
    Furit* CreateFurit()
    {
        return new Banana;
    }
};

class PearFactory:public FuritFactory
{
public:
    Furit* CreateFurit()
    {
        return new Pear;
    }
};

int main(int argc, char const *argv[])
{
    Furit *fur = NULL;
    FuritFactory * fac = new AppleFactory;
    fur = fac->CreateFurit();  //实际= fur = new Apple;
    fur->show();
    delete fac;
    fac = new PearFactory;
    fur = fac->CreateFurit();
    fur->show();
    return 0;
}
