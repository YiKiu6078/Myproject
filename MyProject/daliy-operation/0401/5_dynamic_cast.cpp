#include <iostream>
using namespace std;

class Parent
{
    private:
        int a;
    public:
        virtual void show()
        {
            cout<<"this is parent"<<endl;
        }
};

class Child:public Parent
{
    public:
        int array[102400];
        virtual void show()
        {
            cout<<"this is Child"<<endl;
        }
};

void f(Parent *p)
{
    Child *c = dynamic_cast<Child *>(p);
    if (c != NULL)
    {
        c->array[102400-1] = 100;
        cout<<"转换成功"<<endl;
    }
    else
    {
        cout<<"转换失败"<<endl;
    }
}

int main(int argc, char const *argv[])
{
    Parent *p1 = new Child;
    f(p1);
    delete p1;
    return 0;
}