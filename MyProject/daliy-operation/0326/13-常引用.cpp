#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int a = 1;
    const int &b = a;
    a = 189;
    const int &pd = 200;

    int *pc = (int *)&pd;
    
    (*pc)++;

    cout<<"pd = "<<pd<<endl;
    return 0;
}
