#include <iostream>
using namespace std;

class Parent
{

};

class Child:public Parent
{

};

int main(int argc, char const *argv[])
{
    int a = 1;
    char ch = 'a';
    a = static_cast<int>(ch);
    cout<<a<<endl;

    Parent p;
    Child c;
    p = static_cast<Parent>(c);

    Parent *p1 = static_cast<Parent *>(&c);
    return 0;
}
