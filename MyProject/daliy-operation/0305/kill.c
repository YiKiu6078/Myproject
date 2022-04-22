/*****************************************************
copyright (C), 2014-2015, Lighting Studio. Co.,     Ltd. 
File name：
Author：Jerey_Jobs    Version:0.1    Date: 
Description：
Funcion List: 
*****************************************************/

#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	int ret;

	if((pid = fork()) < 0)
	{
		perror("fork");
		exit(-1);
	}
	if(pid == 0)
	{
	//	raise(SIGSTOP);
		alarm(1);
		while(1);
		exit(0);
	}
	else
	{
		printf("pid = %d\n",pid);
		sleep(2);
		if((waitpid(pid,NULL,WNOHANG)) == 0)
		{
             if((ret = kill(pid,SIGKILL)) == 0)
			 {
				 printf("kill %d\n",pid);
			 }
			 else
			 {
				 perror("kill");
			 }
		}
		else
		{
			printf("child is over\n");
		}
	}

    return 0;
}
