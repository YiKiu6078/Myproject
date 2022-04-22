#include <iostream>
using namespace std;

class Parent
{
    private:
        int a;
    public:
        enum{ID = 0};
        virtual void show()
        {
            cout<<"this is parent"<<endl;
        }
        virtual int GetId()
        {
            return ID;
        }
};

class Child:public Parent
{
    public:
        int array[102400];
        enum{ID = 1};
        virtual void show()
        {
            cout<<"this is Child"<<endl;
        }
        virtual int GetId()
        {
            return ID;
        }
};

void f(Parent *p)
{
    if (p->GetId() == Child::ID)
    {
        Child *c = (Child *)p;
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