#include <iostream>
#include <cstring>
using namespace std;

class Phone
{
public:
    virtual void function() = 0;
};

class CallPhone:public Phone
{
public:
    void function()
    {
        cout<<"打电话的phone"<<endl;
    }
};

class MusicPhone:public Phone
{
private:
    Phone *phone;
public:
    MusicPhone(Phone *p)
    {
        phone = p;
    }
    void function()
    {
        phone->function();
        cout<<"听音乐的phone"<<endl;
    }
};

class OnlinePhone:public Phone
{
private:
    Phone *phone;
public:
    OnlinePhone(Phone *p)
    {
        phone = p;
    }
    void function()
    {
        phone->function();
        cout<<"能上网的phone"<<endl;
    }
};

int main(int argc, char const *argv[])
{
    Phone * callphone = new CallPhone;
    cout<<"打电话"<<endl;
    callphone->function();
    Phone * musicphone = new MusicPhone(callphone);
    cout<<"听音乐"<<endl;
    musicphone->function();
    Phone * onlinephone = new OnlinePhone(musicphone);
    cout<<"上网"<<endl;
    onlinephone->function();
    return 0;
}
