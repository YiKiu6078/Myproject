#include <iostream>
#include <cstring>
using namespace std;

class Mystring
{
private:
    int size;
    char *pstring;
public:
    Mystring();
    Mystring(const char* str);  //有参字符串构造
    Mystring(const Mystring& obj);  //有参类构造

    char& operator[](int Index);  //构造[]运算符；
    Mystring &operator=(const char *str);  //字符串拷贝
    Mystring& operator=(const Mystring &obj);

    void show();
};

Mystring::Mystring()
{
    int size = 0;
    pstring = NULL;
}

Mystring::Mystring(const char* str)
{
    this->size = strlen(str) + 1;
    this->pstring = new char[size];
    strcpy(this->pstring,str);
}

Mystring::Mystring(const Mystring& obj)
{
    this->size = obj.size;
    this->pstring = new char[size];
    strcpy(this->pstring,obj.pstring);
}

char& Mystring::operator[](int Index)
{
    static char ch = -1;
    if ((Index >= 0) && (Index < this->size))
    {
        return this->pstring[Index];
    }
    else
    {
        cout<<"数组越界访问"<<endl;
        return ch;
    }
}

Mystring &Mystring::operator=(const char *str)
{
    this->size = strlen(str) + 1;
    if (this->pstring != NULL)
    {
        delete []pstring;
    }
    pstring = new char[size];
    strcpy(this->pstring,str);
    return *this;
}

Mystring& Mystring::operator=(const Mystring &obj)
{
    this->size = obj.size;
    if (this->pstring != NULL)
    {
        delete []pstring;
    }
    pstring = new char[size];
    strcpy(this->pstring,obj.pstring);
    return *this;
}

void Mystring::show()
{
    cout<<"字符串的长度为："<<this->size<<endl;
    cout<<"字符串的内容为："<<this->pstring<<endl;
}

int main(int argc, char const *argv[])
{
    Mystring s1;
    Mystring s2("what's up");
    s2.show();
    cout<<"s2[1]"<<s2[1]<<endl;


    return 0;
}
