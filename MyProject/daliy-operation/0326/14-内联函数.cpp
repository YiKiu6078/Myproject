#include <iostream>
using namespace std;

inline int Maxnum(int a,int b)
{
    return ((a > b) ? a : b);
}

int main(int argc, char const *argv[])
{
    int i = 1;
    int j = 2;
    int result = Maxnum(i,j);
    cout<<"result = "<<result<<endl;
    return 0;
}
