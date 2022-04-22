#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int pipe_fd[2];
	pid_t pid;
	int p_write1,p_write2;
	int p_read;
	char buf[100];
	memset(buf,0,sizeof(buf));

	if (pipe(pipe_fd) < 0)
	{
	    printf("pipe create error!\n");
		exit(-1);
	}
	if ((pid = fork()) < 0)
	{
	    printf("fork create error!\n");
		exit(-1);
	}
	else if (pid > 0)
	{
		close(pipe_fd[0]);
		p_write1 = write(pipe_fd[1],"what's",6);
		if( p_write1 != -1)
		{
			printf("p_write1 = %d\n",p_write1);
	    	printf("this is parent writing!\n");
		}
		p_write2 = write(pipe_fd[1]," up!",4);
		if( p_write2 != -1)
		{
			printf("p_write2 = %d\n",p_write2);
	    	printf("this is parent writing!\n");
		}
		close(pipe_fd[1]);
		sleep(2);
		waitpid(pid,NULL,0);

	}
	else if (pid == 0)
	{
	    close(pipe_fd[1]);
		sleep(2);
		p_read = read(pipe_fd[0],buf,sizeof(buf));
		if (p_read != -1)
		{
			printf("buf = %s\n",buf);
		    printf("this is child read!\n");
		}

		close(pipe_fd[0]);
		_exit(0);
	}
	
	return 0;
}
