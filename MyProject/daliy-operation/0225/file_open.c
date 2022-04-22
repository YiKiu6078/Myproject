#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 20

int main()
{
    int to_fd;
	char buffer[BUFFER_SIZE];
	int bytes_write;
	char *ptr = "hello";
	int i;
    to_fd = open("three_hello.txt",O_CREAT | O_RDWR,S_IWUSR | S_IRUSR | S_IRGRP);
	if (-1 == to_fd)
	{
	    perror("to_fd error!\n");
		exit(-1);
	}
	lseek(to_fd,0,SEEK_SET);
	for (i = 0;i < 3;i++)
	{
	    memset(buffer,0,sizeof(buffer));
		write(to_fd,ptr,5);
		read(to_fd,buffer,5);
		write(1,buffer,5);
	//	write(1,"\n",1);
	}
	close(to_fd);
	return 0;
}
