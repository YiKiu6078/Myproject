#include <iostream>
using namespace std;
/*
int add(int a,int b)
{
    cout<<"int add"<<endl;
    return a+b;
}
double add(double x,double y)
{
    cout<<"double add"<<endl;
    return x+y;
}
*/
template <typename T>

T add(T x,T y)
{
    cout<<"T add"<<endl;
    return x+y;
}
template <typename T1,typename T2>
void print(T1 x,T2 y)
{
    cout<<x<<" "<<y<<endl;
}
int main(int argc, char const *argv[])
{
    cout<<add(1,2)<<endl;
    cout<<add(1.3,3.1)<<endl;
    cout<<add<int>(1,'a')<<endl;
    print(1,'a');
    return 0;
}
