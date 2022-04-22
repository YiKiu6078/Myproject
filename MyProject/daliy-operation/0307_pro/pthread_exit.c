#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *ret_val()
{
    printf("in this thread!what's up!!!\n ");
	pthread_exit((void *)8);
}

int main()
{
    pthread_t ptid;//线程id;
	int ret;
	int * tmp;

	ret = pthread_create(&ptid,NULL,(void *)ret_val,NULL);
	if (ret != 0)
	{
	    perror("create pthread error!\n");
		exit(0);
	}
	ret = pthread_join(ptid,(void *)&tmp);
	if (ret != 0)
	{
	    perror("join pthread error!\n");
		exit(0);
	}

	printf("join pthread success! is %d\n",(int )tmp);
	return 0;
}
