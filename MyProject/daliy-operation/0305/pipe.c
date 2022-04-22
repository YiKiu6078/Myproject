#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];
	int ret;
	pid_t pid;
	char buffer[100];
    
    ret = pipe(fd);
	if (-1 == ret)
	{
	    perror("pipe error!\n");
		exit(EXIT_FAILURE);
	}
	if ((pid = fork()) < 0)
	{
	    perror("fork error!\n");
		close(fd[0]);
		close(fd[1]);
		exit(-1);
	}
	else if (pid > 0)
	{
	    close(fd[1]);
		sleep(1);

		close(fd[0]);
	}
	else
	{
	    close(fd[0]);

		close(fd[1]);
	}
	return 0;
}
