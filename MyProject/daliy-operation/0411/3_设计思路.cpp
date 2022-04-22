#include <iostream>
using namespace std;

class BankWorker
{
public:
    virtual void Worker() = 0;
};

class GetMoney:public BankWorker
{
public:
    void Worker()
    {
        cout<<"取款业务"<<endl;
    }
};

class SaveMoney:public BankWorker
{
public:
    void Worker()
    {
        cout<<"存款业务"<<endl;
    }
};

int main(int argc, char const *argv[])
{
    BankWorker* b = new GetMoney;
    b->Worker();
    delete b;
    b = new SaveMoney;
    b->Worker();
    delete b;
    return 0;
}
