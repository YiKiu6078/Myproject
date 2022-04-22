#include <iostream>
#include <memory>
using namespace std;

class Test1
{
public:
    Test1()
    {
        cout<<"Test 的构造函数"<<endl;
    }
    ~Test1()
    {
        cout<<"Test 的析构函数"<<endl;
    }
    void show()
    {
        cout<<"what's up"<<endl;
    }
};

void f1()
{
    Test1 *p1 = new Test1;
}

void f2()
{
    auto_ptr<Test1>my_menmory(new Test1);
    my_menmory->show();
}

int main(int argc, char const *argv[])
{
 //   f1();
    f2();
    return 0;
}
