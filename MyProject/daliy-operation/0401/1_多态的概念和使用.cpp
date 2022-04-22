#include <iostream>
using namespace std;

class Parent
{
    public:
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
    p = c;
    p.show();

    Parent *p1 = new Child;
    p1->show();
    delete p1;

    p1 = new Parent;
    p1->show();
    return 0;
}
