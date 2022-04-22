#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    const int a = 1;

    int *p = const_cast<int *>(&a);
    cout<<*p<<endl;
    *p = 100;
    cout<<a<<endl;

    const int &m = 1;
    int &n = const_cast<int &>(m);
    n = 100;

    cout<<m<<endl;
    cout<<n<<endl;
    return 0;
}
