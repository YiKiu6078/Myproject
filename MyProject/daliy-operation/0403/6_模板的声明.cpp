#include <iostream>
using namespace std;
template <typename T>

class Test
{
private:
    int a;
public:
    Test(T a);

    void show();

    ~Test();
}; 

template <typename T>
Test<T>::Test(T a)
{
    this->a = a;
}
template <typename T>
void Test<T>::show()
{
    cout<<a<<endl;
}

template <typename T>
Test<T>::~Test()
{
    cout<<"Test的析构函数"<<endl;
}

int main(int argc, char const *argv[])
{
    Test<int>t(1);
    t.show();
    return 0;
}
