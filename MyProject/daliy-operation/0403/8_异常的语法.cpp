#include <iostream>
using namespace std;

int Div(int x,int y)
{
    if (0 == y)
    {
        throw 0;
    }
    return x / y;
}

int main(int argc, char const *argv[])
{
    int a,b;
    cin>>a>>b;

    try
    {
        cout<<Div(a,b)<<endl;
    }

    catch(int)
    {
        cout<<"zero exception"<<endl;
    }
    cout<<"nihao"<<endl;
    return 0;
}
