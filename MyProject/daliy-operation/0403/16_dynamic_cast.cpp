#include <iostream>
using namespace std;

class Parent
{
public:
    virtual void show(){};
};

class Child:public Parent
{
public:
    void show(){};
};

int main(int argc, char const *argv[])
{
    Child *c = new Child;
    Parent *p;
    delete c;
//    c = static_cast<Child *>(new Parent);
    c = dynamic_cast<Child *>(new Parent);//强制转换
    if (c == NULL)
    {
        cout<<"转换失败"<<endl;
    }
    else
    {
        cout<<"转换成功"<<endl;
        delete c;
    }

    return 0;
}
