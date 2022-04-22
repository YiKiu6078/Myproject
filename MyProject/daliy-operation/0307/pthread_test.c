#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

char msg[] = "ni hao";

void * work_tid(void * arg)
{
    printf("this is msg %s\n",(char *)arg);
	
	strcpy(arg,"what's up!\n");

	sleep(3);

	pthread_exit("this work thread is over!");
}

int main()
{
    pthread_t tid;
	int ret;
	char * work_val;
	
	ret = pthread_create(&tid,NULL,work_tid,(void *)msg);
	if (ret != 0)
	{
	    perror("create pthread error!");
		exit(-1);
	}

	printf("this is join waitting...\n");

	ret = pthread_join(tid,(void *)&work_val);

	if (ret != 0)
	{
	    perror("join pthread error!\n");
		exit(-1);
	}
    printf("pthread joined , value is %s\n",(char *)work_val);

	printf("msg is %s\n",msg);
	return 0;
}
