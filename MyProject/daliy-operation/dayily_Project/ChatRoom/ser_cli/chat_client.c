#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVPORT 8888

struct msg_node
{
    char chat_mode[5];
    int connfd;
    char chat_msg[100];
};

void *write_func(void * arg)
{
    int clifd;
    int choice;
    char write_buf[100];
    struct msg_node msg_text;
    
    clifd = *((int *)arg);
    
    while(1)
    {
        memset(write_buf,0,100);
        memset(msg_text.chat_msg,0,100);
        memset(msg_text.chat_mode,0,5);
        printf("please select chat mode:\n");
        printf("1.send to all  2.send to one\n");
        scanf("%d",&choice);
        getchar();
        printf("please input chat content:\n");
        fgets(write_buf,sizeof(write_buf),stdin);
        if (1 == choice)
        {
            strcpy(msg_text.chat_mode,"stoa");
        }
        else if (2 == choice)
        {
            strcpy(msg_text.chat_mode,"stoo");
            printf("please input number of friend:\n");
            scanf("%d",&msg_text.connfd);
         //   getchar();
        }
        else 
        {
            printf("choice error!\n");
            exit(-1);
        }
        strcpy(msg_text.chat_msg,write_buf);
        int ret = send(clifd,&msg_text,sizeof(msg_text),0);
        if (-1 == ret)
        {
            printf("send message fail!\n");
            exit(-1);
        }
    }
    return NULL;  
}

void *read_func(void *arg)
{
    int clifd;
    int nread;
    char readline[100];
    struct msg_node msg_text;
    
    clifd = *((int *)arg);

    while(1)
    {
        nread = recv(clifd,readline,sizeof(readline),0);
        readline[nread] = '\0';
        fputs(readline,stdout);
    }
    pthread_exit(NULL);
}

int main(int argc,char **argv)
{
    int clifd;
    socklen_t len;
    pthread_t read_tid,write_tid;// 创建读写线程分离；
    struct sockaddr_in servaddr,cliaddr;

    if (argc != 2)
    {
        printf("need input ip address!\n");
        exit(0);
    }
    
    clifd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVPORT);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = connect(clifd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    if (-1 == ret)
    {
        printf("connect server error!\n");
        exit(-1);
    }

    ret = pthread_create(&write_tid,NULL,(void *)write_func,(void *)&clifd);
    if (-1 == ret)
    {
        printf("create write thread error!\n");
        exit(-1);
    }
    
    ret = pthread_create(&read_tid,NULL,(void *)read_func,(void *)&clifd);
    if (-1 == ret)
    {
        printf("create read thread error!\n");
        exit(-1);
    }
    pthread_detach(write_tid);
 //   pthread_detach(read_tid);

//    pthread_join(write_tid,NULL);
    pthread_join(read_tid,NULL);
    close(clifd);
    return 0;
}