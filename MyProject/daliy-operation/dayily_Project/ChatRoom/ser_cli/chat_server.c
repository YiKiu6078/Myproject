#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <ctype.h>

#define SERVPORT 8888

enum {MALLOC_OK = 1,MALLOC_NO,CREATE_OK,CREATE_NO};

typedef struct client_online  //创建在线客户机链表包含id,套接口和客户机地址
{
    int id;
    int connfd;
    struct sockaddr_in cliaddr;

    struct client_online *next;
}C_Online;

struct pthread_node  //线程节点结构体用来传递链表和套接口 
{
    int connfd;
    C_Online * head;
};

struct msg_node    //该结构体用于接收消息使用客户机和服务器该结构体应该保持一致
{
    char chat_mode[5]; //定义聊天方式
    int connfd;    //聊天对象
    char chat_msg[100];  //聊天内容
};

int is_malloc_ok(C_Online * newnode)
{
    if (NULL == newnode)
    {
        printf("malloc error!\n");
        return MALLOC_NO;
    }
    return MALLOC_OK;
}

int create_node(C_Online ** newnode)
{
    *newnode = (C_Online *)malloc(sizeof(C_Online));
    if (MALLOC_OK == is_malloc_ok(*newnode))
    {
        return CREATE_OK;
    }
    else
    {
        printf("create node error!\n");
        return CREATE_NO;
    }
}

void create_link(C_Online  ** head)
{
    if (create_node(head) == CREATE_OK)
    {
        (*head)->next = NULL;
    }
    else
    {
        printf("create link error!\n");
        exit(EXIT_FAILURE);
    }
}

void insert_node_head(C_Online *head,C_Online *newnode)
{
    newnode->next = head->next;
    head->next = newnode;
}

void release_link(C_Online ** head) //释放链表
{
    C_Online *p = NULL;
    p = (*head)->next;
    while (p != NULL)
    {
        (*head)->next = p->next;
        free(p);
        p = (*head)->next;
    }
    free(*head);
    *head = NULL;
}

void delete_node(struct pthread_node * func_par_node)
{
    C_Online * p1 = NULL;
    C_Online * p2 = NULL;
    C_Online * head = NULL;
    int connfd;

    head = func_par_node->head;
    connfd = func_par_node->connfd;

    p1 = head;
    p2 = head->next;
    if (NULL == p2)
    {
        printf("link is empty!\n");
    }
    else
    {
        while (p2 != NULL && p2->connfd != connfd)
        {
            p1 = p2;
            p2 = p2->next;
        }
        if (NULL == p2)
        {
            printf("no such client!\n");
        }
        else
        {
            p1->next = p2->next;
            free(p2);
        }
    }
}

void send_to_one(struct pthread_node ** func_par_node,struct msg_node * msg_one)
{
    int n;
    C_Online * p = NULL;
    p = (*func_par_node)->head->next;
    n = strlen(msg_one->chat_msg);
    while (p != NULL && p->connfd != msg_one->connfd)
    {
        p = p->next;
    }
    if (NULL == p)
    {
        printf("client %d is not online!\n",msg_one->connfd);
    }
    else
    {
        send(p->connfd,msg_one->chat_msg,n,0);
    }
}

void send_to_all(C_Online * head,char chat_msg[])
{
    C_Online * p = NULL;
    int n;
    n = strlen(chat_msg);
    p = head->next;
    while(p != NULL)
    {
        send(p->connfd,chat_msg,n,0);
        p = p->next;
    }
}

void msg_send_recv(struct pthread_node * func_par_node)
{
    int i,n,m;
    struct msg_node msg_text;
    memset(msg_text.chat_msg,0,100);
    n = recv(func_par_node->connfd,&msg_text,sizeof(msg_text),0);
    if (0 == n)
    {
        printf("client  %d is offline\n",func_par_node->connfd);
        delete_node(func_par_node);    //将下线的客户机对应节点删除
        pthread_exit(NULL);
    }
    else
    {
        m = strlen(msg_text.chat_msg);
        msg_text.chat_msg[m] = '\0';
        printf("received the following:\n");
        printf("%s\n",msg_text.chat_msg);
        for (i = 0;i < m;i++)
        {
            msg_text.chat_msg[i] = toupper(msg_text.chat_msg[i]);
        }
        if (0 == strcmp(msg_text.chat_mode,"stoa"))    //如果等于send to all表示群聊；
        {
            send_to_all(func_par_node->head,msg_text.chat_msg);//需要接受聊天内容，对象是全体在线成员
        }
        else if (0 == strcmp(msg_text.chat_mode,"stoo"))
        {
            send_to_one(&func_par_node,&msg_text);    //发送聊天消息，需要对象节点，
        }
        else
        {
            printf("chat mode error!\n");
        }
    }
}

void * cli_chat(void * arg)
{
    struct pthread_node func_par_node;
    func_par_node = *((struct pthread_node *)arg);
    while(1)
    {
        msg_send_recv(&func_par_node);
    }
    close(func_par_node.connfd);
    return NULL;
}

int main()
{
    int listenfd,connfd;
    socklen_t len;
    pthread_t tid;
    C_Online * head = NULL;
    C_Online * newnode = NULL;
    struct sockaddr_in servaddr,cliaddr;
    struct pthread_node func_par_node;  //定义线程函数参数结构体

    create_link(&head);    //创建链表
    func_par_node.head = head;//将创建好的头节点赋值于函数参数结构体，此时结构体包含了链表；

    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if (-1 == listenfd)
    {
        perror("listen socket error!\n");
        exit(EXIT_FAILURE);
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVPORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    listen(listenfd,1024);

    while (1)
    {
        len = sizeof(cliaddr);
        connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&len);
        func_par_node.connfd = connfd;

        create_node(&newnode);
        newnode->connfd = connfd;
        insert_node_head(head,newnode);

        //pthread_create(&tid,NULL,(void *)cli_chat,(void *)&connfd);这时候若是传递第四个参数为connfd
        //则无法将链表传递过去，传递链表的话，connfd--连接的套接口则无法传递，因此需要定义一个结构体来传递链表和connfd;
        pthread_create(&tid,NULL,(void *)cli_chat,(void *)&func_par_node);
    }

    close(listenfd);  
    release_link(&head); 
    return 0;
}