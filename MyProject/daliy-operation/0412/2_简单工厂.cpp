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
    Furit* CreateApple()
    {
        return new Apple;
    }
    Furit* CreateBanana()
    {
        return new Banana;
    }
    Furit* CreatePear()
    {
        return new Pear;
    }
};

int main(int argc, char const *argv[])
{
    Furit *fur = NULL;
    FuritFactory * fac = new FuritFactory;
    fur = fac->CreateApple();  //实际= fur = new Apple;
    fur->show();
    return 0;
}
