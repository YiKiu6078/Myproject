#include <iostream>
using namespace std;

class a
{
public:
    a()
    {
        cout<<"a"<<endl;
    }
    ~a()
    {
        cout<<"a的析构"<<endl;
    }
};

class b:public a
{
public:
    b()
    {
        cout<<"b"<<endl;
    }
    ~b()
    {
        cout<<"b的析构"<<endl;
    }
};
int main(int argc, char const *argv[])
{
    b B;
    return 0;
}
