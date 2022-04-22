#include <iostream>
using namespace std;

int DDiv(int x,int y)
{
    if (0 == y)
    {
        throw 0;
    }
    return x / y;
    cout<<"33"<<endl;
}

int Div(int a,int b)
{
    DDiv(a,b);
    cout<<"111"<<endl;
    return 1;
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
