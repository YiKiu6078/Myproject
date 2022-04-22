#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int i;
	pid_t pid;
	pid = fork();

	if (pid < 0)
	{
	    perror("fork error!");
		exit(-1);
	}
	else if(pid > 0)
	{
	    for (i = 0;i < 3;i++)
		{
		    printf("this is parent running!\n");
			sleep(1);
		}
	}
	else
	{
	    execl("./main","main","1","2","3","4",NULL);
		printf("********************\n");
	}
	return 0;
}
