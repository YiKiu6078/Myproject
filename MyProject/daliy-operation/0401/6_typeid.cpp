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
    if (typeid(*p) == typeid(Child))
    {
        Child *c = (Child *)(p);
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
    int a;
    char ch;
    Parent p;
    Child c1;
    const type_info &pa = typeid(a);
    const type_info &pb = typeid(ch);
    const type_info &pc = typeid(p);
    const type_info &pd = typeid(c1);

    cout<<pa.name()<<endl;
    cout<<pb.name()<<endl;
    cout<<pc.name()<<endl;
    cout<<pd.name()<<endl;
    Parent *p1 = new Child;
    f(p1);
    delete p1;
    return 0;
}