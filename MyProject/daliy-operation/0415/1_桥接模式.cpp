#include <iostream>
using namespace std;

class Phone
{
public:
    virtual void fun() = 0;
};

class XIAOMI:public Phone
{
public:
    void fun()
    {
        cout<<"xiaomi"<<endl;
    }
};

class HUAWEI:public Phone
{
public:
    void fun()
    {
        cout<<"huawei"<<endl;
    }
};

class soft
{
protected:
    Phone * phone;
public:
    virtual void fun() = 0;
};

class QQ:public soft
{
public:
    QQ(Phone *p)
    {

        phone = p;
    }
    void fun()
    {
        cout<<"using QQ"<<endl;
    }
};

class WeChat:public soft
{
public:
    WeChat(Phone *p)
    {

        phone = p;
    }
    void fun()
    {
        cout<<"using WeChat"<<endl;
    }
};

int main(int argc, char const *argv[])
{
    Phone *p = new XIAOMI;
    soft *s = new WeChat(p);
    s->fun();
    return 0;
}
