#include <iostream>
#include <cstring>
#include <unistd.h>
using namespace std;

class Singleton
{
private:
    static int count;
    static Singleton* m_instance;
    Singleton()
    {

    }
public:
    static Singleton *Getinstance()
    {
    /*    if (NULL == m_instance)
        {
            m_instance = new Singleton;    //懒汉式整个系统只new1次；
        }*/
        count++;
        return m_instance;
    }

    static int Getcount()
    {
        return count;
    }
    void Release()
    {
        if (0 == count && m_instance != NULL)
        {
            delete m_instance;
        }
    }
};

Singleton*Singleton::m_instance = new Singleton;
int Singleton::count = 0;


int main(int argc, char const *argv[])
{
    //所有指针指向同一个内存空间

    Singleton * s1 = Singleton::Getinstance();
    Singleton * s2 = Singleton::Getinstance();
    Singleton * s3 = Singleton::Getinstance();
    Singleton * s4 = Singleton::Getinstance();
    Singleton * s5 = Singleton::Getinstance();

    cout<<Singleton::Getinstance()<<endl;
    cout<<s1<<endl;
    cout<<s2<<endl;
    cout<<s3<<endl;
    cout<<s4<<endl;
    cout<<s5<<endl;  //s1-5地址相同

    return 0;
}
