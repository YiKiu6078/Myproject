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
#include <string.h>

struct msg
{
    long msg_types;
    char msg_buf[512];
};

int main()
{
    int qid;
    int pid;
    int len;
    struct msg pmsg;

    pmsg.msg_types = getpid();
    sprintf(pmsg.msg_buf,"hello! this is %d \n\0",getpid());
    len = strlen(pmsg.msg_buf);
    qid = msgget(IPC_PRIVATE,IPC_CREAT|0666);
    //qid = msgget(0,IPC_CREAT|0666);
    msgsnd(qid,&pmsg,len,0);
    printf("succesfully send a message to queue:%d\n",qid);
    //system("ipcs -q");
     
    return 0;
}
