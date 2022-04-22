#include <iostream>
using namespace std;
template <typename T,typename U>

class Parent
{
protected:
    T a;
    U b;
public:
    Parent(T a,U b)
    {
        this->a = a;
        this->b = b;
    }
    void show()
    {
        cout<<a<<" "<<b<<endl;
    }
};

class Child:public Parent<int,char>
{
public:
    Child(int a,char b):Parent(a,b)
    {

    }
    void show()
    {
        cout<<a<<" "<<b<<endl;
    }
};

template <typename T,typename U>
class Child2:public Parent<T,U>
{
private:
    U c;
public:
    Child2(T a,U b,U c):Parent<T,U>(a,b)
    {
        this->c = c;
    }
    void show()
    {
        cout<<this->a<<" "<<this->b<<endl;
    }
};

int main(int argc, char const *argv[])
{
    Child c1(1,'s');
    c1.show();

    Child2<int,double> c2(1,2.1,1.3);
    c2.show();
    
    return 0;
}
