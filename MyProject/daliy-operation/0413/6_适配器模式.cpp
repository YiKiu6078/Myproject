#include <iostream>
using namespace std;

class Current
{
public:
    virtual int GetCurrent() = 0;
};

class Current_220:public Current
{
public:
    int GetCurrent()
    {
        return 220;
    }
};

class Adapter:public Current
{
private:
    Current * current;
public:
    Adapter(Current * c)
    {
        current = c;
    }
    int GetCurrent()
    {
        if (current->GetCurrent() == 220)
        {
            return 12;
        }
        else
        {
            return 5;
        }
    }
};

class Phone
{
private:
    Current *current;
public:
    Phone(Current *c)
    {
        current = c;
    }
    void Start()
    {
        if(current->GetCurrent() == 12)
        {
            cout<<"充电中……"<<endl;
        }
        else if(current->GetCurrent() == 220)
        {
            cout<<"这不裂开啊……"<<endl;
        }
    }
};

int main(int argc, char const *argv[])
{
    Current *c = new Current_220;
    Adapter *a = new Adapter(c);
    Phone * p = new Phone(a);
 //   Phone * p = new Phone(c);
    p->Start();
    return 0;
}
