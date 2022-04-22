#include <iostream>
using namespace std;

class Test
{
public:
    Test()
    {
        cout<<"Test的构造函数"<<endl;
    }
    Test(const Test &obj)
    {
        cout<<"Test的拷贝构造函数"<<endl;
    }
    void print()
    {
        cout<<"Test exception"<<endl;
    }

    ~Test()
    {
        cout<<"Test的析构函数"<<endl;
    }
};

int Div(int x,int y)
{
    if (0 == y)
    {
        throw Test();
        throw new Test;
    }
    return x / y;
}


int main(int argc, char const *argv[])
{
    int a,b;
    cin>>a>>b;

    try
    {
        cout<<Div(a,b)<<endl;
    }

    catch(Test &t)
    {
        t.print();
    }
    catch(Test *t)
    {
        t->print();
        delete t;
    }
    cout<<"nihao"<<endl;
    return 0;
}
