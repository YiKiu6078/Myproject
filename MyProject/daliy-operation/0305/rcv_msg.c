/*****************************************************
copyright (C), 2014-2015, Lighting Studio. Co.,     Ltd. 
File name：
Author：Jerey_Jobs    Version:0.1    Date: 
Description：
Funcion List: 
*****************************************************/

#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>

#define BUFSZ 4096

struct msg
{
    long msg_types;
    char msg_buf[512];
};

int main(int argc,char ** argv)
{
    int qid;
    int len;
    struct msg pmsg;
    if(argc != 2)
    {
        perror("argc");
    }
    qid = atoi(argv[1]);
    len = msgrcv(qid,&pmsg,BUFSZ,0,0);
    if(len > 0)
    {
        pmsg.msg_buf[len] = '\0';
        printf("qid %d\n",qid);
        printf("msg type %d\n",pmsg.msg_types);
        printf("msg text %s\n",pmsg.msg_buf);
    }
    else if( len  == 0)
    {
        printf("no message!\n");
    }
    else
    {
        perror("msgrcv\n");
    }
    //system("ipcs -q");

    return 0;
}
