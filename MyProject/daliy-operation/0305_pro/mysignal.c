#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void fuc(int signal)
{
    if (SIGINT == signal)
	{
	    printf("what's up!\n");
	}
	if (SIGQUIT == signal)
	{
		printf("O no!\n");
	}
}

int main()
{
    pid_t pid;
	pid = fork();
	if (pid < 0)
	{
	    printf("create fork error!\n");
		exit(-1);
	}
	else if (0 == pid)
	{
	    printf("waitig for signal SIGINT or SIGQUIT:\n");
		signal(SIGINT,fuc);
		signal(SIGQUIT,fuc);

		pause();
	}
	else if (pid > 0)
	{
		int cmd;
		printf("plase input 1 or 2 :\n");
		scanf("%d",&cmd);
		if (1 == cmd)
		{
		    kill(pid,SIGINT);
		}
		if (2 == cmd)
		{
		    kill(pid,SIGQUIT);
		}
	}

	return 0;
}
