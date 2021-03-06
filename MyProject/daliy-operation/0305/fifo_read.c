/*****************************************************
copyright (C), 2014-2015, Lighting Studio. Co.,     Ltd. 
File name：
Author：Jerey_Jobs    Version:0.1    Date: 
Description：
Funcion List: 
*****************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <memory.h>

#define FIFO_SEVER "/tmp/fifosever"

int main(int argc,char **argv)
{
    char r_buf[4096*2];
    int fd;
    int r_size;
    int ret_size;
    r_size = atoi(argv[1]);
    printf("requore real read bytes %d\n",r_size);
    memset(r_buf,0,sizeof(r_buf));
    fd = open (FIFO_SEVER,O_RDONLY|O_NONBLOCK);
    if(fd == -1)
    {
        printf("open %s for read error!\n");
        exit(0);
    }
    while(1)
    {
        memset(r_buf,0,sizeof(r_buf));
        ret_size = read(fd,r_buf,r_size);
        if(ret_size == -1)
        {
            if(errno == EAGAIN)
                printf("no data avalible\n");
        }
        printf("real read bytes %d\n",ret_size);
        sleep(1);
    }
    pause();
    unlink(FIFO_SEVER);

    return 0;
}
