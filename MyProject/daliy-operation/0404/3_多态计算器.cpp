#include <iostream>
using namespace std;

class AbstractCalculator
{
public:
    virtual int GetResult()
    {
        return 0;
    }

    int num1;
    int num2;
};

class AddCalculator:public AbstractCalculator
{
public:
    int GetResult()
    {
        return num1 + num2;
    }
};

class SubCalculator:public AbstractCalculator
{
public:
    int GetResult()
    {
        return num1 - num2;
    }
};

class MulCalculator:public AbstractCalculator
{
public:
    int GetResult()
    {
        return num1 * num2;
    }
};

int main(int argc, char const *argv[])
{
    AbstractCalculator * ac = new  AddCalculator;
    ac->num1 = 100;
    ac->num2 = 10;
    cout<<ac->num1<<" + "<<ac->num2<<" = "<<ac->GetResult()<<endl;
    delete ac;
    ac = new  SubCalculator;
    ac->num1 = 100;
    ac->num2 = 10;
    cout<<ac->num1<<" - "<<ac->num2<<" = "<<ac->GetResult()<<endl;
    delete ac;
    ac = new  MulCalculator;
    ac->num1 = 100;
    ac->num2 = 10;
    cout<<ac->num1<<" * "<<ac->num2<<" = "<<ac->GetResult()<<endl;
    delete ac;
    return 0;
}
