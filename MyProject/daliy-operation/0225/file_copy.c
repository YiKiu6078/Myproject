#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc,char **argv)
{
    int from_fd,to_fd;
	int bytes_read,bytes_write;
	char buffer[BUFFER_SIZE];
    char *ptr = NULL;
	
    if (argc != 3)
	{
	    printf("need fromfile!\n");
		exit(0);
	}

	from_fd = open(argv[1],O_CREAT|O_RDONLY,S_IRUSR|S_IWUSR);
	if (from_fd == -1)
	{
	    perror("fromfile error!\n");
		exit(-1);
	}
	if ((to_fd = open(argv[2],O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR|S_IRGRP)) == -1)
	{
	    perror("to_fd error!\n");
		exit(-1);
	}
	while (bytes_read = read(from_fd,buffer,BUFFER_SIZE))
	{
	    if (-1 == bytes_read)
		{
		    perror("read error!\n");
			break;
		}
		else if (bytes_read > 0)
		{
		    ptr = buffer;
			while (bytes_write = write(to_fd,ptr,bytes_read))
			{
			    if (-1 == bytes_write)
				{
				    perror("write error!\n");
					break;
				}
				else if (bytes_read == bytes_write)
				{
				    break;
				}
				else if(bytes_write > 0)
				{
				    ptr = ptr + bytes_write;
					bytes_read = bytes_read - bytes_write;
				}
				if (bytes_read == bytes_write)
				{
				    break;
				}
			}
		}
	}

	close(from_fd);
	close(to_fd);

	return 0;
}
