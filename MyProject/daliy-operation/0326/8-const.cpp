#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    const int a = 1;
    int *p = (int *)&a;
    *p = 2;
    printf("a = %d,*p = %d\n",a,*p);
    return 0;
}
