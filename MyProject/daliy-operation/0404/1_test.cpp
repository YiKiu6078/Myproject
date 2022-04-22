#include <iostream>
using namespace std;

class Parent
{
public:
    int a = 1;
protected:
    int b = 2;
private:
    int c = 3;
};

class Son :public Parent
{
public:
    int c = 4;
};

int main(int argc, char const *argv[])
{
    Son s;
    cout<<"sizeof(son) = "<<sizeof(s)<<endl;
    cout<<"sizeof(Parent) = "<<sizeof(Parent)<<endl;
    return 0;
}
