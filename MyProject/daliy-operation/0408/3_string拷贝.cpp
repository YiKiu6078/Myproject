#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char const *argv[])
{
    string s1 = "hello";
    string s2 = "hellw";
    
    if (0 == s1.compare(s2))
    {
        cout<< "s1 = s2" <<endl;
    }
    else if(s1.compare(s2) > 0)
    {
        cout << "s1 > s2" <<endl;
    }
    else
    {
        cout << "s1 < s2" <<endl;
    }

    string SubStr = s1.substr(1,3);
    cout<<"SubStr = "<<SubStr<<endl;

    string s3 = "www.baidu@qq.com";
    int p = s3.find('@');
    s1 = s3.substr(p + 1,2);
    cout<<s1<<endl;
    return 0;
}
