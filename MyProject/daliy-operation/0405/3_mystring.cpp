#include <iostream>
using namespace std;

class MyString
{
private:
    int size;
    char *pstring;
public:
    MyString();  //无参初始化;
    MyString(const char * str);
    MyString(const MyString& obj);

    ~MyString();
};

MyString::MyString()
{
    size = 0;
    pstring = NULL;
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
