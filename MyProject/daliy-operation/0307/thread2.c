/*****************************************************
copyright (C), 2014-2015, Lighting Studio. Co.,     Ltd. 
File name：
Author：Jerey_Jobs    Version:0.1    Date: 
Description：
Funcion List: 
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int flag = 1;

void * thread_function(void * arg);

int main()
{
	int ret;
    pthread_t tid;
	void * thread_result;
	int count = 1;

	ret = pthread_create(&tid,NULL,thread_function,NULL);

	if(ret != 0)
	{
		perror("thread create failed!\n");
		exit(EXIT_FAILURE);
	}

	while(count++ < 10)
	{
		if(flag == 1)
		{
			printf("1");
			flag = 2;
		}
		else
		{
			sleep(1);
		}
	}

	printf("\nwaiting for thread to finish...\n");

	ret = pthread_join(tid,&thread_result);

	if(ret != 0)
	{
		perror("thread join failed!\n");
		exit(EXIT_FAILURE);
	}
	
    return 0;
}

void * thread_function(void *arg)
{
	int count = 1;
	while(count++ < 10)
	{
		if(flag == 2)
		{
			printf("2");
			flag = 1;
		}
		sleep(1);
	}
}

