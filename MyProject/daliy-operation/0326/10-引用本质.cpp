#include <iostream>
using namespace std;

struct test
{
    int &a;
    int &c;
    char &b;
};


int main(int argc, char const *argv[])
{
    int a = 1;
    char b = 'c';
    int &pa = a;
    char &pb = b;
    cout<<sizeof(pa)<<endl;
    cout<<sizeof(pb)<<endl;
    cout<<sizeof(test)<<endl;
    return 0;
}
