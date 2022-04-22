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
#include <memory.h>
#include <stdlib.h>

#define FIFO_SEVER "/tmp/fifosever"

int main(int argc,char *argv[])
{
    int fd;
    char w_buf[4096*2];
    int real_wnum;
    
    memset(w_buf,0,4096*2);

    if((mkfifo(FIFO_SEVER,O_CREAT|O_EXCL) < 0) && (errno != EEXIST))
    {
        printf("cannt create fifosever!\n");
        exit(0);
    }
    fd = open(FIFO_SEVER,O_WRONLY|O_NONBLOCK);
    if(fd == -1)
    {
        if(errno == ENXIO)
            printf("open error,no reading process\n");
    }
    scanf("%s",w_buf);
    real_wnum = write(fd,w_buf,2048);
    if(real_wnum == -1)
    {
        if(errno == EAGAIN)
        {
            printf("write to fifo error try later!\n");
        }
    }
    else
    {
        printf("real write num is %d\n",real_wnum);
    }

    return 0;
}
