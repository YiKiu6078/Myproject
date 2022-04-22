#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc,char ** argv)
{
    int a = 111;
    int fd;
    if ((fd = open("a.txt",O_RDONLY)) == -1)
    {
        perror("open file error");
        return -1;
    }
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fail to fork!\n");
        return -1;
    }
    else if(pid > 0)
    {
        printf("this is parent process!\n");
        char buffer[50] = "";
        if (read(fd,buffer,30) == -1)
        {
            perror("fail to read!\n");
            return -1;
        }
        printf("buffer = [%s]\n",buffer);

    }
    else
    {
        sleep(1);
        printf("this is son process!\n");
        char buffer[50] = "";
        if (read(fd,buffer,30) == -1)
        {
            perror("fail to read!\n");
            return -1;
        }
        printf("buffer = [%s]\n",buffer);
    }
    return 0;
}