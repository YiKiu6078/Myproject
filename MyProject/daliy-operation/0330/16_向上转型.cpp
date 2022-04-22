#include <iostream>
using namespace std;

class Parent
{
    private:
        int m_a;
};

class Child:public Parent
{
    private:
        int m_a;
};

int main(int argc, char const *argv[])
{
    int a = 1.11;
    double b = 2;
    Parent p;
    Child c;
    p = c;
    return 0;
}
