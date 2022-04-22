#include <iostream>
using namespace std;

class Parent
{
    public:
        int a;
        virtual void show()
        {
            cout<<"this is parent"<<endl;
        }
};

class Child:public Parent
{
    public:
        virtual void show()
        {
            cout<<"this is Child"<<endl;
        }
};

int main(int argc, char const *argv[])
{
    Child c;
    Parent p;
    cout<<sizeof(c)<<endl;
    cout<<sizeof(p)<<endl;
    cout<<"Parent对象的地址"<<&p<<endl;
    cout<<"成员变量a的起始地址"<<&p.a<<endl;

    cout<<"Child对象的地址"<<&c<<endl;
    cout<<"child成员变量a的起始地址"<<&c.a<<endl;
    return 0;
}
