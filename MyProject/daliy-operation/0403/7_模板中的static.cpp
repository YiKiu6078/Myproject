#include <iostream>
using namespace std;
template <typename T>

class Test
{
private:
    int a;
public:
    static int count;
public:
    Test(T a);

    void show();

    ~Test();
}; 

template <typename T>
int Test<T>::count = 0;

template <typename T>
Test<T>::Test(T a)
{
    this->a = a;
    count++;
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
    Test<int>t0(1);
    Test<int>t1(1);
    Test<int>t2(1);
    Test<int>t3(1);
    Test<int>t4(1);
    Test<int>t5(1);
    
    Test<char>t6('l');
    Test<char>t7('s');
    Test<char>t8('b');

    cout<<Test<int>::count<<endl;
    cout<<Test<char>::count<<endl;
    return 0;
}
