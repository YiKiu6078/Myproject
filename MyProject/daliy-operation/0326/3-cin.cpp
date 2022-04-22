#include <iostream>
using namespace std;

void test()
{
    int a = 111;
    char b = 'h';
    char c[] = "what's up";
    float d = 5.2132178;
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    cout<<"c = "<<c<<endl;
    cout<<"d = "<<d<<endl;
}

void test2()
{
    int a,b,c;
    cin>>a>>b>>c;
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    cout<<"c = "<<c<<endl;
}

int main(int argc, char const *argv[])
{
    test(); 
    test2();   
    return 0;
}
