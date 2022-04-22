#include <iostream>
using namespace std;

//int Div(int x,int y)throw(int,char);
int Div(int x,int y);
//int Div(int x,int y)throw();


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
    catch(char)
    {
        cout<<"char exception"<<endl;
    }
    catch(double)
    {
        cout<<"double exception"<<endl;
    }

    cout<<"nihao"<<endl;
    return 0;
}

int Div(int x,int y)
{
    if (0 == y)
    {
        throw 1.11;
    }
    return x / y;
}