#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void my_func(int sign_no)
{
	if(sign_no==SIGINT)
		printf("hello world\n");
	else if(sign_no==SIGQUIT)
	{
		printf("eixt!\n");
		exit(1);
	}
}
int main()
{
	pid_t pid;


	pid = fork();


	if(pid == 0)
	{
	    printf("Waiting for signal SIGINT or SIGQUIT \n ");
	
	    /*注册信号处理函数*/
	    signal(SIGINT, my_func);
	    signal(SIGQUIT, my_func);
	
	     pause();
	}
	if(pid > 0)
	{
		int cmd;

		scanf("%d",&cmd);


		if(cmd == 1)
		{
			kill(pid,SIGINT);
		}

		if(cmd == 2)
		{
			kill(pid,SIGQUIT);
		}
    } 
}

