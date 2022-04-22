#include "c_s.h"

typedef struct msg    //创建结构体
{
    int flag;    //标志位：1、注册 2、登录
    int account;//存放账号
    char name[20];
    char password[16];
	char chat_msg[50];//聊天内容
	char mode[5];    //聊天方式
	int recv_reg;//注册返回值
	int recv_log;//登录返回值
	int state;  //状态信息
}MSG;

typedef struct online_usr   //创建在线用户链表--保存在线用户信息；
{
    char name[20];
	int account;
	int connfd;

	struct online_usr * next;
}Online;

struct thread_node  //包含套接口，数据库
{
    int connfd;  //客户端套接口
	sqlite3 * db;
	Online * head;
};

int create_table(sqlite3 * db)
{
    char * sql = NULL;
    char * errmsg = NULL;

    sql = "create table if not exists usr_info (account integer primary key,name text,password text);";
    int ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
    if (SQLITE_OK != ret)
    {
        printf("create table error!%s\n",errmsg);
        return SQLITE_NO;
    }
    return SQLITE_OK;
}

int is_malloc_ok(Online * newnode)
{
    if (NULL == newnode)
	{
	    return MALLOC_NO; 
	}
	return MALLOC_OK;
}

int create_node(Online ** newnode)
{
    *newnode = (Online *)malloc(sizeof(Online));
	if (MALLOC_OK != is_malloc_ok(*newnode))
	{
	    return CREATE_NODE_NO;
	}
	return CREATE_NODE_OK;
}

void create_link(Online ** head)
{
    if (CREATE_NODE_OK == create_node(head))
	{
		(*head)->next = NULL;
	}
	else 
	{
	    perror("create link error!");
		exit(-1);
	}
}

void insert_node(Online * head,Online * newnode) //将节点插入链表
{
    newnode->next = head->next;
	head->next = newnode;
}

#if 1
void display(Online * head)
{
	Online * p = NULL;
	p = head->next;
	printf("this is display!\n*************************\n");
	while (p != NULL)
	{
		printf("name = %s\n",p->name);
		printf("account = %d\n",p->account);
		printf("connfd = %d\n",p->connfd);
		p = p->next;
	}

}
#endif

void release_link(Online ** head)  //释放链表；
{
    Online * p = NULL;
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

void reg_usr(struct thread_node * TNode,MSG * msg_info)//注册用户
{
    char sql[SQL_SIZE];
	char *errmsg = NULL;
	int ret;

	sqlite3_open("chat_database.db",&TNode->db);

//	read(msg->connfd,&msg_info,sizeof(msg_info));
	printf("注册用户名为：%s\n",msg_info->name);
	printf("正在生成账号：\n");
	srand((unsigned)time(NULL));
	int count = 100000 + rand() % 1000000;
//	int count = rand() % 100;
    msg_info->account = count;
	printf("已生成账号为%d\n",msg_info->account);
	sprintf(sql,"insert into usr_info values (%d,'%s','%s');",msg_info->account,msg_info->name,msg_info->password);

	ret = sqlite3_exec(TNode->db,sql,NULL,NULL,&errmsg);
	printf("ret = %d\n",ret);
	if (SQLITE_OK != ret)
	{
		printf("register user fail!%s\n",errmsg);
		sqlite3_close(TNode->db);
		pthread_exit(NULL);
	}
    msg_info->recv_reg = REG_OK;
	sqlite3_close(TNode->db);
}

void login_usr(struct thread_node * TNode,MSG * msg_info)//登录用户
{
	char sql[SQL_SIZE];
	char * errmsg = NULL;
	char ** result = NULL;
	int n_row,n_col;
	int ret;
	int count,i;
	Online * usrnode = NULL;
//	Online usr_info;   //在线用户信息
//	int account = msg_info->account;
//	ret = is_exist(TNode);
	sqlite3_open("chat_database.db",&TNode->db);
	create_node(&usrnode); //创建节点；
	usrnode->connfd = TNode->connfd;
	
	sprintf(sql,"select * from usr_info where account = %d;",msg_info->account);
	ret = sqlite3_get_table(TNode->db,sql,&result,&n_row,&n_col,&errmsg);
	printf("4 = %s, 6 = %s\n",result[3],result[5]);//查找到账号，密码；
	if (SQLITE_OK == ret)
	{
		count = atoi(result[3]);
		printf("account = %d\n",count);
		if ((msg_info->account == count) && (0 == strcmp(msg_info->password,result[5])))
		{
	  	    msg_info->recv_log = LOG_OK;//表示登录成功
			
			strcpy(usrnode->name,result[4]); //将登陆后的用户姓名插入在线链表
			usrnode->account = count;   //将登录后的用户账号插入在线链表
			insert_node(TNode->head,usrnode);//将头节点信息插入链表
			display(TNode->head); 
		}
		else
		{
		    msg_info->recv_log = LOG_NO;
		}
	}
	else
	{
	    printf("select scord error!%s\n",errmsg);
    	sqlite3_free_table(result);
	}
//	write(TNode->connfd,&msg_info,sizeof(msg_info));

    sqlite3_free_table(result);
	sqlite3_close(TNode->db);
}

int do_operation(struct thread_node * TNode)
{
	int n_read;
	MSG msg_info;
	while (1)
	{
		memset(&msg_info,0,sizeof(msg_info));
		n_read = read(TNode->connfd,&msg_info,sizeof(MSG));
/*	if (0 == n_read)
	{
		printf("client %d had offline!\n",TNode->connfd);
		return ;
	}
	else
	{
	printf("reg_name = %s\n",msg_info.name);
*/
		int flag = msg_info.flag;
   		if (1 == flag)  //注册
		{
	   		reg_usr(TNode,&msg_info);
			write(TNode->connfd,&msg_info,sizeof(msg_info));	
		}
		else if(2 == flag)  //登录
		{
			login_usr(TNode,&msg_info);
			write(TNode->connfd,&msg_info,sizeof(msg_info));
			break;
		}
		else if(3 == flag)
		{
	   	//	admin_login(TNode,&msg_info);  //管理员登录
		}
		else
		{
	   		printf("operation error!\n");
		}
		
	}
	return n_read;
//	}
}

int is_offline(struct thread_node * TNode)//判断是否下线
{
    int n_read;
	MSG msg_info;
	n_read = read(TNode->connfd,&msg_info,sizeof(msg_info));
	return n_read;
}

void delete_node(struct thread_node * TNode)  //客户机下线则删除客户机在线节点
{
    Online * p1 = NULL;    
    Online * p2 = NULL;    
    Online * head = NULL;
	int connfd = TNode->connfd;
	head = TNode->head;
	p1 = head;
	p2 = head->next;
	if (p2 == NULL)
	{
	    printf("链表为空!\n");
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
		    printf("没有这个用户！\n");
		}
		else
		{
		    p1->next = p2->next;
			free(p2);
		}
	}
}

void send_to_one(struct thread_node ** TNode, MSG * msg_info)//私聊
{
    Online * p = NULL;
	int n,m;
	char name[20];
	char send_msg[100];

	p = (*TNode)->head->next;
	memset(send_msg,0,sizeof(send_msg));

	while (p != NULL && p->connfd != (*TNode)->connfd) //找到当前选择私聊的客户机套接口
	{
	    p = p->next;
	}
	if (NULL == p)
	{
	    printf("客户机不存在！\n");
	}
	else
	{
		strcpy(name,p->name);
	}

	p = (*TNode)->head->next;
	m = strlen(msg_info->chat_msg);
	msg_info->chat_msg[m] = '\0';
	sprintf(send_msg,"用户%s想对你悄咪咪说：%s",name,msg_info->chat_msg);

	while (p != NULL && p->account != msg_info->account) //查找需要发送消息对象的账号
	{
	    p = p->next;
	}
	if (NULL == p)
	{
	    msg_info->state = OFFLINE;
		printf("需要发送的用户不在线！\n");
	}
	else
	{
	    msg_info->state = ONLINE;
		write(p->connfd,&send_msg,sizeof(send_msg));
	}
}

void send_to_all(struct thread_node ** TNode,MSG * msg_info)//群聊
{
    Online * p = NULL;
	int n,m;
	char name[20];
	char send_msg[100];
	p =(*TNode)-> head->next;
	memset(send_msg,0,sizeof(send_msg));
	while (p != NULL && p->connfd != (*TNode)->connfd) //找到当前选择群聊的客户机套接口
	{
	    p = p->next;
	}
	if (NULL == p)
	{
	    printf("链表为空！\n");
	}
	else
	{
		strcpy(name,p->name);
	}
	m = strlen(msg_info->chat_msg);
	msg_info->chat_msg[m] = '\0';
	sprintf(send_msg,"用户%s想对大家说：%s",name,msg_info->chat_msg);
	while (p != NULL)
	{
	    if (p->connfd != (*TNode)->connfd)
		{
		    write(p->connfd,&send_msg,sizeof(send_msg));
		}
		p = p->next;
	}
}

void send_recv_msg(struct thread_node * TNode)
{
    MSG msg_info;
	int m,nrecv,ret;
    memset(&msg_info,0,sizeof(msg_info));
	nrecv = read(TNode->connfd,&msg_info,sizeof(msg_info));

	if (0 == nrecv)
	{
	    printf("client %d had offline!\n",TNode->connfd);
    	delete_node(TNode);
		pthread_exit(NULL);
	}
	else
	{
/*	    m = strlen(msg_info.chat_msg);
		msg_info.chat_msg[m] = '\0';
		printf("%d号客户机想要发送的内容为：%s\n",msg_info.chat_msg);
*/
		if (0 == strcmp(msg_info.mode,"stoo"))
		{
		    send_to_one(&TNode,&msg_info);
		}
		else if(0 == strcmp(msg_info.mode,"stoa"))
		{
		    send_to_all(&TNode,&msg_info);
		}
		else
		{
		    printf("chat mode error!\n");
		}
	}

}

void *work_func(void *arg)
{
	struct thread_node TNode;
	int ret;
	TNode = *((struct thread_node *)arg);
	do_operation(&TNode);
	while(1)
	{
		ret = is_offline(&TNode);
		if (0 == ret)
		{
			printf("client %d had offline!\n",TNode.connfd);
		}
		send_recv_msg(&TNode);
	}
	close(TNode.connfd);
}

int main()
{
	sqlite3 * db;  //定义数据库变量
    int listenfd,connfd;
    socklen_t len;
    pthread_t tid;
    struct sockaddr_in  servaddr,cliaddr;
	struct thread_node TNode;

 	//创建数据库
	int ret = sqlite3_open("chat_database.db",&db);
	if (SQLITE_OK != ret)
	{
    	printf("open database error!\n");
    	exit(EXIT_FAILURE);
	}
    //创建表
	if (SQLITE_OK != create_table(db))
	{
    	printf("create table failure!\n");
    	sqlite3_close(db);
    	return 0;
	}
	TNode.db = db;
	sqlite3_close(db);

	//创建链表
	Online * head = NULL;

	create_link(&head);

    //开始socket
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    //配置
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVPORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));//绑定

    listen(listenfd,1024);//监听
    
    //开始创建连接
    while(1)
    {
        len = sizeof(cliaddr);
        connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&len);
        TNode.connfd = connfd;
		printf("client %d had connected!\n",connfd);
		TNode.head = head; //将头节点放入线程参数里
        //创建线程；
        int ret = pthread_create(&tid,NULL,(void *)work_func,(void *)&TNode);
		if(0 == ret)
		{
			perror("thread error!\n");
			exit(-1);
		}
    }
	
	release_link(&head);  //释放链表
	close(listenfd);   //关闭套接口
    return 0;
}
