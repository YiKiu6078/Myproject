#include <iostream>
using namespace std;

class Test
{
private:
    int a;
    void f1(){}
public:
    int b;
    void f2(){
        cout<<"b = "<<b<<endl;
    }
protected:
    int c;
    void f3(){}
};

int main(int argc, char const *argv[])
{
    Test t1;
    t1.b = 2;
    t1.f2();
    return 0;
}
