#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int a = 1,b = 0;
    int num = (a > b) ? a : b;
    cout<<"num = "<<num<<endl;
    (a < b) ? a : b = 100;
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;

    return 0;
}
