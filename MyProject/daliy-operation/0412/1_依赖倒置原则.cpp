#include <iostream>
#include <cstring>
using namespace std;

class BankWorkA
{
public:
    virtual void work() = 0;
};

class BankWorkB
{
public:
    virtual void work() = 0;
};

class GetMoney:public BankWorkA
{
public:
    void work()
    {
        cout<<"get money from bankA..."<<endl;
    }
};

class SaveMoney:public BankWorkB
{
public:
    void work()
    {
        cout<<"save money to bankB..."<<endl;
    }
};

class Person  //相当于中间层来操作，具体的都是通过person来调用
{
private:
    GetMoney * m_get;
    SaveMoney * m_save;
public:
    Person(GetMoney * get,SaveMoney * save)
    {
        m_get = get;
        m_save = save;
    }
    void work()
    {
        m_get->work();
        m_save->work();
    }
};

int main(int argc, char const *argv[])
{
    GetMoney * get = new GetMoney;
    SaveMoney *save = new SaveMoney;
    Person * p = new Person(get,save);
    p->work();
    return 0;
}
