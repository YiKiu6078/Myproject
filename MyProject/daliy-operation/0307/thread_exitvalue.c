/*****************************************************
copyright (C), 2014-2015, Lighting Studio. Co.,     Ltd. 
File name：
Author：Jerey_Jobs    Version:0.1    Date: 
Description：
Funcion List: 
*****************************************************/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

char message[]="hello world!\n";

void * thread_function(void * arg)
{
    printf("thread_function is running! argument is %s\n",(char *)arg);
    sleep(3);
    strcpy(message,"bye");
    pthread_exit("thank for your CPU time!\n\a");
}

int main()
{
    int res;
    pthread_t a_thread;
    void * thread_result;

    res = pthread_create(&a_thread,NULL,thread_function,(void *)message);
    printf("waiting for thread to finish!\n");
    res = pthread_join(a_thread,&thread_result);
    printf("thread joined, it returned %s\n",(char *)thread_result);
    printf("message is now %s\n",message);

    return 0;
}
