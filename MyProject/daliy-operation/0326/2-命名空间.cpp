#include <iostream>
using namespace std;

namespace zhang
{
    int num = 666;
    void func()
    {
        cout<<"nihao zhang"<<endl;
    }
}

namespace liu
{
    int num = 999;
    void func()
    {
        cout<<"nihao liu"<<endl;
    }
}

void test()
{
    cout<<"zhang num = "<<zhang::num<<endl;
    cout<<"liu num = "<<liu::num<<endl;
}

void test2()
{
    using zhang::num;
    cout<<"zhang num = "<<num<<endl;
    num = 521;
    cout<<"zhang num = "<<num<<endl;
}
using namespace liu;
void test3()
{
    cout<<"liu num = "<<num<<endl;
}
int main(int argc, char const *argv[])
{
    //test();
    //test2();
    test3();
    return 0;
}

