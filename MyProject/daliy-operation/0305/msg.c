#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

struct msg_buf
    {
        int mtype;
        char data[255];
    };
 
int main()
{
        key_t key;
        int msgid;
        int ret;
        struct msg_buf msgbuf;
        struct msg_buf msgbuf1;
        struct msg_buf msgbuf2;
        struct msg_buf msgbuf3;
 
        key=ftok("/tmp/2",'a');
        printf("key =[%x]\n",key);
        msgid=msgget(key,IPC_CREAT|0666); /*ͨ���ļ���Ӧ*/

        if(msgid==-1)
        {
                printf("create error\n");
                return -1;
        }
 
        msgbuf1.mtype = 1;
        strcpy(msgbuf1.data,"test haha1");
        msgbuf2.mtype = 2;
        strcpy(msgbuf2.data,"test haha2");
        msgbuf3.mtype = 3;
        strcpy(msgbuf3.data,"test haha3");

        ret=msgsnd(msgid,&msgbuf1,sizeof(msgbuf1.data),IPC_NOWAIT);
        ret=msgsnd(msgid,&msgbuf2,sizeof(msgbuf2.data),IPC_NOWAIT);
        ret=msgsnd(msgid,&msgbuf3,sizeof(msgbuf3.data),IPC_NOWAIT);
        if(ret==-1)
        {
                printf("send message err\n");
                return -1;
        }
 
        //memset(&msgbuf,0,sizeof(msgbuf));
        ret=msgrcv(msgid,&msgbuf,sizeof(msgbuf.data),2,IPC_NOWAIT);
        if(ret==-1)
        {
                printf("recv message err\n");
                return -1;
        }
        printf("recv msg =[%s]\n",msgbuf.data);
 
}
