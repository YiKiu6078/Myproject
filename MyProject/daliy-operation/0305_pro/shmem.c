#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main(int argc,char **argv)
{
   	int shmid;
	pid_t pid;
   	char *p_addr,*c_addr;
	
	if (2 != argc)
	{
	    fprintf(stderr,"usage:%s\n\a",argv[0]);// \a 为响铃；
		exit(1);
	}
	if ((shmid = shmget(IPC_PRIVATE,1024,IPC_CREAT)) == -1)
	{
	    fprintf(stderr,"creaete share Memory error!%s\n\a",strerror(error));
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
	    p_addr = shmat(shmid,NULL,0);//内存映射！
		memset(p_addr,'\0',1024);
		strncpy(p_addr,argv[1],1024);
		wait(NULL);
		exit(0);
	}
	else
	{
	    sleep(1);
		c_addr = shmat(shmid,NULL,0);
		printf("client get %p\n",c_addr);
	}
	return 0;
}
