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
        virtual ~Parent()
        {
            cout<<"Parent的析构函数"<<endl;
        }
};

class Child:public Parent
{
    public:
        virtual void show()
        {
            cout<<"this is Child"<<endl;
        }
        ~Child()
        {
            cout<<"Child的析构函数"<<endl;
        }
};

int main(int argc, char const *argv[])
{
    Parent *p1 = new Child;
    p1->show();
    delete p1;
    p1 = NULL;
    return 0;
}
