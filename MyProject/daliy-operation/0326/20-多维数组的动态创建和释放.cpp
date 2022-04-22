#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int ** a = new int *[5];
    for(int i = 0; i < 5; i++)
    {
        a[i] = new int[6];
    }

    for(int i = 0; i < 5; i++)
    {
        delete[]a[i];
        a[i] = NULL;
    }
    delete []a;
    a = NULL;
    return 0;
}
