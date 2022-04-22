/*****************************************************
copyright (C), 2014-2015, Lighting Studio. Co.,     Ltd. 
File name：
Author：Jerey_Jobs    Version:0.1    Date: 
Description：
Funcion List: 
*****************************************************/

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>

char message[]="hello world!";
void * thread_function(void *arg)
{
    printf("thread function is running, argument is %s\n",(char *)arg);
    sleep(3);
    pthread_exit("thank you for your CPU time! \n");
}

int main()
{
    pthread_t a_thread;
    void * thread_result;
    int ret;
    
    ret = pthread_create(&a_thread,NULL,(void *)thread_function,(void *)message);

    if(ret != 0)
    {
        perror("create thread error");
        exit(0);
    }

    printf("waiting for thread to finish...\n");

    ret = pthread_join(a_thread,&thread_result);
    if(ret != 0)
    {
        perror("thread join error");
        exit(0);
    }
    
    printf("thread joined,it returned %s\n",(char*)thread_result);
     printf("message is now %s\n",message);

    return 0;
}
