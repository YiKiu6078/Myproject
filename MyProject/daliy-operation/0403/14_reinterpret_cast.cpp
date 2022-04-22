#include <iostream>
using namespace std;



int main(int argc, char const *argv[])
{
    int a = 100;
    int b = 100;
    char *p = reinterpret_cast<char *>(&a); 
    cout<<*(p + 1)<<endl;   

    int *q = reinterpret_cast<int *>(100);

    *q = 1;
    return 0;
}
