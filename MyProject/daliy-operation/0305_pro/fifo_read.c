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
	char r_buf[4096*2];
	int f_read;
	int read_size;

	read_size = atoi(argv[1]);
	memset(r_buf,0,sizeof(r_buf));
	fd = open(FIFO_SERVER,O_RDONLY | O_NONBLOCK);
	if (fd == -1)
	{
	    if(errno == EEXIST)
		{
		    printf("open fifoserver error!\n");
		}
		exit(-1);
	}

	while (1)
	{
	    memset(r_buf,0,sizeof(r_buf));
		f_read = read(fd,r_buf,read_size);
		if (-1 == f_read)
		{
		    printf("read error!\n");
			if (errno == EAGAIN)
			{
			    printf("no date avalible\n");
			}
		}
		printf("real read bytes %d\n",read_size);
		printf("real read is %s\n",r_buf);
		sleep(1);
	}
	pause();
	unlink(FIFO_SERVER);
	return 0;

}
