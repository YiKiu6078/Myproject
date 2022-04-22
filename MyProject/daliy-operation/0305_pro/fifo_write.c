#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define FIFO_SERVER "./tmp/fifoserver"

int main(int argc,char ** argv)
{
	int fd;
	char w_buf[4096*2];
	int f_write;

	memset(w_buf,0,sizeof(w_buf));
	if ((mkfifo(FIFO_SERVER,O_CREAT | O_EXCL) < 0) && (errno != EEXIST))
	{
	    printf("create fifoserver error!\n");
		exit(0);
	}
	fd = open(FIFO_SERVER,O_WRONLY | O_NONBLOCK);
	printf("%d\n",fd);
	if (fd == -1)
	{
	    if(errno == ENXIO)
		{
		    printf("open fifoserver error!\n");
		}
		exit(-1);
	}
	printf("****\n");
	scanf("%s",w_buf);
	f_write = write(fd,w_buf,sizeof(w_buf));

	if (f_write == -1)
	{
	    printf("write error!\n");
		exit(-1);
	}
	else
	{
	    printf("real write num is %d\n",f_write);
	}
	return 0;
}
