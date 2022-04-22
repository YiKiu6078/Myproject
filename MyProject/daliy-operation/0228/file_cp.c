#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc ,char ** argv)
{
    int from_fd;
    int to_fd;
    int n_write;
    int n_read;
    char buffer[BUFFER_SIZE];
    char *ptr = NULL;

    if (argc != 3)
    {
        printf("need file name!\n");
        exit(0);
    }

    from_fd = open(argv[1],O_CREAT | O_RDONLY,S_IRUSR | S_IWUSR);
    if (-1 == from_fd)
    {
        perror("open from file error!\n");
        exit(-1);
    }

    to_fd = open(argv[2],O_CREAT | O_WRONLY,S_IRUSR | S_IWUSR | S_IRGRP);
    if (-1 == to_fd)
    {
        perror("open to file error!\n");
        exit(-1);
    }

    //n_read = read(from_fd,buffer,BUFFER_SIZE);
    while (n_read = read(from_fd,buffer,BUFFER_SIZE))
    {
        if((n_read == -1) && (errno != EINTR))
        {
            perror("read error!\n");
            break;
        }
        else if(n_read > 0)
        {
            ptr = buffer;
            while (n_write = write(to_fd,ptr,n_read))
            {
                if ((-1 == n_write) && (errno != EINTR))
                {
                    perror("write file error!\n");
                    break;
                }
                else if (n_write == n_read)
                {
                    break;
                }
                else if(n_write > 0)
                {
                    ptr = ptr + n_write;
                    n_read = n_read - n_write;
                }
                if (n_write == -1)
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
