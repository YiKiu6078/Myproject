#include <iostream>
using namespace std;

class Parent
{
    public:
        virtual void show() = 0;
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

    Parent *p1 = new Child;
    p1->show();
    delete p1;
    return 0;
}
