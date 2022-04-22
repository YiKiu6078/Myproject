#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;
pthread_mutex_t mutex;

class Signleton
{
public:
    static Signleton*m_instance;
    static int count;
    Signleton()
    {

    }
public:
    static Signleton * GetInstance()
    {
        if (NULL == m_instance)
        {
            cout<<"m_instance is NULL"<<endl;
            usleep(100000);
            m_instance = new Signleton;
        }
        count++;
        return m_instance;
    }
    static int GetCount()
    {
        return count;
    }
    static void Release()
    {
        count--;
        if (count == 0 && m_instance != NULL)
        {
            delete m_instance;
        }
    }
};

Signleton *Signleton::m_instance = new Signleton;
int Signleton::count = 0;

void *CreateInstace(void *arg)
{
    pthread_mutex_trylock(&mutex);
    Signleton * s = Signleton::GetInstance();
    cout<<s<<endl;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[])
{
    Signleton *s1 = Signleton::GetInstance();
    Signleton *s2 = Signleton::GetInstance();
    Signleton *s3 = Signleton::GetInstance();
    Signleton *s4 = Signleton::GetInstance();
    Signleton *s5 = Signleton::GetInstance();
    Signleton *s6 = Signleton::GetInstance();
    cout<<Signleton::GetCount()<<endl;
    cout<<s1<<endl;
    cout<<s2<<endl;
    cout<<s3<<endl;
    cout<<s4<<endl;
    cout<<s5<<endl;
    cout<<s6<<endl;

    pthread_mutex_init(&mutex,NULL);

    int ret;
    pthread_t tid[10];
    for(int i = 0;i < 10;i++)
    {
        ret = pthread_create(&tid[i],NULL,CreateInstace,NULL);
    }

    void *status;
    for(int i = 0;i < 10;i++)
    {
        pthread_join(tid[i],&status);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}
