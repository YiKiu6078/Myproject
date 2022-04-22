#include <unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>

#define BUFFER_SIZE 1024

int main(int argc , char **argv)
{
    int from_fd,to_fd;
    int bytes_read,bytes_write;
    char buffer[BUFFER_SIZE];
    char *ptr;

    if(argc != 3)
    {
        fprintf(stderr,"usage:%s fromfile tofile\n\a",argv[0]);
	exit(1);
    }

    //open source file
    if((from_fd = open(argv[1],O_RDONLY)) == -1)
    {
        fprintf(stderr,"open %s Error:%s\n",argv[1],strerror(errno));
	exit(1);
    }

    //create target file
    if((to_fd = open(argv[2],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR)) == -1)
    {
        fprintf(stderr,"open %s Error:%s\n",argv[2],strerror(errno));
	exit(1);
    }

    //file copy
    while(bytes_read = read(from_fd,buffer,BUFFER_SIZE))
    {
        //error found
	if((bytes_read == -1)&&(errno != EINTR))
	    break;
	else if(bytes_read > 0)
	{
	    ptr = buffer;
	    while(bytes_write = write(to_fd,ptr,bytes_read))
	    {
	        //error found
	        if((bytes_write == -1)&&(errno != EINTR))
	               break;
		//write all bytes
		else if(bytes_read == bytes_read)
		    break;
		//write part bytes
		else if(bytes_write > 0)
		{
		    ptr += bytes_write;
		    bytes_read -= bytes_write;
		}
	    }
            //error found when write
	    if(bytes_write ==-1)
	        break;
	}
    }
    close(from_fd);
    close(to_fd);

    return 0;
}
