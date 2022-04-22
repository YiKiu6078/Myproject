#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int *p = new int;
    *p = 100;
    cout<<"*p = "<<*p<<endl;
    delete p;
    p = NULL;

    int *q = new int(200);
    cout<<"*q = "<<*q<<endl;
    delete q;
    q = NULL;

    int *q2 = new int[5]{1,2,3,4,5};
    for (int i = 0;i < 5;i++)
    {
        cout<<"q2[i] = "<<q2[i]<<endl;
    }
    delete []q2;
    q2 = NULL;
    return 0;
}
