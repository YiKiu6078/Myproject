#include <iostream>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
using namespace std;
pthread_mutex_t mutex;
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
        if (NULL == m_instance)
        {
            cout<<"m_instance is NULL"<<endl;
            usleep(100000);
            m_instance = new Singleton;    //懒汉式整个系统只new1次；
        }
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

Singleton*Singleton::m_instance = NULL;
int Singleton::count = 0;

void *CreateInstance(void *arg)
{
    pthread_mutex_trylock(&mutex);
    Singleton * s = Singleton::Getinstance();
    cout<<s<<endl;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[])
{
    //所有指针指向同一个内存空间
/*
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
*/
    pthread_mutex_init(&mutex,NULL);
    int ret;
    void *status;
    pthread_t tid[10];
    for (int i = 0;i < 10;i++)
    {
        ret = pthread_create(&tid[i],NULL,CreateInstance,NULL);
        if (0 != ret)
        {
            perror("create pthread");
        }
    }
    for (int i = 0;i < 10;i++)
    {
        pthread_join(tid[i],&status);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}
