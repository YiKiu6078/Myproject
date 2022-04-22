#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    char ch;
    char buf[32] = {0};

 //   cin>>ch;

 //   ch = cin.get();
  //  cin.get(ch);
 //   cin.get(buf,10);
//    cin.getline(buf,10);
    ch = cin.peek();
    cout<<ch<<endl;
    cin>>buf;

    cout<<buf<<endl;
    return 0;
}
