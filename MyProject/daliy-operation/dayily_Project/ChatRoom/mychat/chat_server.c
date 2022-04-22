#include "c_s.h"

typedef struct msg    //创建结构体
{
    int flag;    //标志位：1、注册 2、登录 3、4 群聊私聊 5、注册VIP 6、修改密码 7、查看所有在线用户
    int account;  //账号
    char name[NAME_SIZE];
    char password[16];
	char chat_msg[MSG_SIZE]; //聊天内容；
	char online_name[NAME_SIZE][NAME_SIZE];  //所有在线人名
	char filename[16];
	char file[1024];
	int online_num; //在线人数
	int online_account[50];  //所有在线账号
	int recv_val; //标志为REG_OK时表示注册成功；标志为LOG_OK时表示登录成功；
	int vip;      // 1 = vip用户 ； 0 = 普通用户
	int forbid;   //forbid = 1 禁言； = 0 解禁言；
	int state;    //状态信息(账号存在EXIST_OK/NO，是否在线ONLINE，OFFLINE)
}MSG;

MSG msg_info;

typedef struct online_usr   //创建在线用户链表--保存在线用户信息；
{
    char name[NAME_SIZE];
	int vip;
	int account;
	int forbid;
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

    sql = "create table if not exists usr_info (account integer primary key,name text,password text,vip integer,forbid integer);";
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
		printf("vip = %d\n",p->vip);
		printf("forbid = %d\n",p->forbid);
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

void reg_usr(struct thread_node TNode)//注册用户
{
    char sql[SQL_SIZE];
	char *errmsg = NULL;
	int ret;

//	sqlite3_open("chat_database.db",&TNode.db);

	printf("注册用户名为：%s\n",msg_info.name);
	printf("正在生成账号：\n");
	srand((unsigned)time(NULL));
	int count = 100000 + rand() % 1000000;

    msg_info.account = count;
	printf("已生成账号为%d\n",msg_info.account);
	sprintf(sql,"insert into usr_info values (%d,'%s','%s',%d,%d);",msg_info.account,msg_info.name,msg_info.password,0,0);

	ret = sqlite3_exec(TNode.db,sql,NULL,NULL,&errmsg);
	printf("ret = %d\n",ret);
	if (SQLITE_OK != ret)
	{
		printf("register user fail!%s\n",errmsg);
		sqlite3_close(TNode.db);
		pthread_exit(NULL);
	}

	msg_info.flag = 1;
    msg_info.recv_val = REG_OK;
	write(TNode.connfd,&msg_info,sizeof(msg_info));
//	sqlite3_close(TNode.db);
}

void login_usr(struct thread_node TNode)//登录用户
{
	char sql[SQL_SIZE];
	char * errmsg = NULL;
	char ** result = NULL;
	int n_row,n_col;
	int ret;
	int count,i;
	Online * usrnode = NULL;
//	sqlite3_open("chat_database.db",&TNode.db);
	create_node(&usrnode); //创建节点；
	usrnode->connfd = TNode.connfd;
	
	sprintf(sql,"select * from usr_info where account = %d;",msg_info.account);
	ret = sqlite3_get_table(TNode.db,sql,&result,&n_row,&n_col,&errmsg);
	if (ret != SQLITE_OK)
	{
		printf("select error!%s\n",errmsg);
		pthread_exit(NULL);
	}
	printf("6 = %s, 8 = %s\n",result[5],result[7]);//查找到账号，密码；
	if (SQLITE_OK == ret)
	{
		count = atoi(result[5]);
		printf("account = %d\n",count);
		if ((msg_info.account == count) && (0 == strcmp(msg_info.password,result[7])))
		{
	  	    msg_info.recv_val = LOG_OK;//表示登录成功
			
			strcpy(usrnode->name,result[6]); //将登陆后的用户姓名插入在线链表
			usrnode->vip = atoi(result[8]);  //将数据库里VIP标志插入在线链表里的VIP标志；
			usrnode->account = count;   //将登录后的用户账号插入在线链表
			usrnode->forbid = atoi(result[9]);
			msg_info.forbid = usrnode->forbid;
			strcpy(msg_info.name,usrnode->name);
			msg_info.vip = usrnode->vip;
			insert_node(TNode.head,usrnode);//将头节点信息插入链表
			display(TNode.head); 
		}
		else
		{
		    msg_info.recv_val = LOG_NO;
		}
	}
	else
	{
	    printf("select scord error!%s\n",errmsg);
    	sqlite3_free_table(result);
	}
	write(TNode.connfd,&msg_info,sizeof(msg_info));
    sqlite3_free_table(result);
//	sqlite3_close(TNode.db);
}

void reg_vip(struct thread_node TNode)    //注册vip
{
	char sql[SQL_SIZE];
	char * errmsg = NULL;
	char ** result = NULL;
	int n_row,n_col;
	int ret;
	
//	sqlite3_open("chat_database.db",&TNode.db);
	sprintf(sql,"select * from usr_info where account = %d;",msg_info.account);
	ret = sqlite3_get_table(TNode.db,sql,&result,&n_row,&n_col,&errmsg);
	if (ret != SQLITE_OK)
	{
		printf("select error!%s\n",errmsg);
		pthread_exit(NULL);
	}
	if (0 == n_row)  //此时表示在数据库中没有找到账号；客户机需要先注册；
	{
		printf("未在数据库中找到该账号！\n");
		msg_info.vip = 0;
	}
	else if (1 == n_row)
	{
		printf("已在数据库中找到该账号！\n");
		msg_info.vip = 1;
		memset(sql,0,SQL_SIZE);
		sprintf(sql,"update usr_info set vip=1 where account=%d;",msg_info.account);
		ret = sqlite3_exec(TNode.db,sql,NULL,NULL,&errmsg);
		if(SQLITE_OK != ret)
		{
			printf("update error!%s\n",errmsg);
		}
		else
		{
			printf("该用户已经成功注册为vip!\n");
		}
	}
	write(TNode.connfd,&msg_info,sizeof(msg_info));
//	sqlite3_close(TNode.db);
}

void delete_node(struct thread_node TNode)  //客户机下线则删除客户机在线节点
{
    Online * p1 = NULL;    
    Online * p2 = NULL;    
    Online * head = NULL;
	int connfd = TNode.connfd;
	head = TNode.head;
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

void send_to_one(struct thread_node TNode)//私聊
{
    Online * p = NULL;
	int n,m;
	char name[NAME_SIZE];

	p = TNode.head->next;

	while (p != NULL && p->connfd != TNode.connfd) //找到当前选择私聊的客户机套接口
	{
	    p = p->next;
	}
	if (NULL == p)
	{
	    printf("客户机不存在！\n");
	}
	else
	{
		strcpy(msg_info.name,p->name);
	}

	p = TNode.head->next;
	m = strlen(msg_info.chat_msg);
	msg_info.chat_msg[m] = '\0';
	printf("用户%s想对你悄咪咪说：%s\n",msg_info.name,msg_info.chat_msg);
//	memset(msg_info.chat_msg,0,sizeof(msg_info.chat_msg));
	while (p != NULL && p->account != msg_info.account) //查找需要发送消息对象的账号
	{
		p = p->next;
	}
	if (NULL == p)
	{
	    msg_info.state = OFFLINE;
		printf("需要发送的用户不在线！\n");
	}
	else  //表示找到需要发送消息的客户机账号
	{
	//	msg_info.flag = 3;
	    msg_info.state = ONLINE;
	}
	write(p->connfd,&msg_info,sizeof(msg_info));
}

void send_to_all(struct thread_node TNode)  //群聊
{
    Online * p = NULL;
	int n,m;
	char name[NAME_SIZE];

	p =TNode.head->next;
	while (p != NULL && p->connfd != TNode.connfd) //找到当前选择群聊的客户机套接口
	{
	    p = p->next;
	}
	if (NULL == p)
	{
	    msg_info.state = EXIST_NO;  //当前在线用户太少；
		write(p->connfd,&msg_info,sizeof(msg_info));
		return ;
	}
	else  //找到群发消息客户机本身的用户名
	{
		if (p->forbid == FORB_OK)
		{
			msg_info.state = MSG_NO;
			write(p->connfd,&msg_info,sizeof(msg_info));
		}
		else
		{
			strcpy(msg_info.name,p->name);
			m = strlen(msg_info.chat_msg);
			msg_info.chat_msg[m] = '\0';
			printf("用户%s想对大家说：%s",name,msg_info.chat_msg);
			p =TNode.head->next;
			while (p != NULL)
			{
	    		if (p->connfd != TNode.connfd)
				{
					msg_info.state = EXIST_OK;
		  	  		write(p->connfd,&msg_info,sizeof(msg_info));
				}
				p = p->next;
			}
		}	
	}
}

void update_password(struct thread_node TNode)  //修改密码
{
	Online * p = NULL;
	Online * q = NULL;
	char sql[SQL_SIZE];
	char * errmsg = NULL;
	int ret;

//	sqlite3_open("chat_database.db",&TNode.db);
	q = TNode.head;
	p = TNode.head->next;
	while (p != NULL && p->connfd != TNode.connfd)
	{
		q = p;   
		p = p->next;
	}
	if (NULL == p)
	{
		printf("Link is empty!\n");
		msg_info.state = CHANGE_NO;
		return ;
	}
	else
	{
		sprintf(sql,"update usr_info set password='%s' where account=%d;",msg_info.password,p->account);
		ret = sqlite3_exec(TNode.db,sql,NULL,NULL,&errmsg);
		if (SQLITE_OK != ret)
		{
			printf("update password error!%s",errmsg);
			msg_info.state = CHANGE_NO;
			return ;
		}
		q->next = p->next;
		free(p);    //密码修改后用户下线重新登录；
		msg_info.state = CHANGE_OK;
	}
	write(TNode.connfd,&msg_info,sizeof(msg_info));
//	sqlite3_close(TNode.db);
}

void seek_online(struct thread_node TNode)
{
	Online * p = NULL;
	int count = 0;
	int i = 0;
	p = TNode.head->next;
	if (NULL == p)
	{
		printf("Link is empty!\n");
		msg_info.state = SEEK_NO;
	}
	else
	{
		while(p != NULL)
		{
			count++;
			strcpy(msg_info.online_name[i],p->name);
			msg_info.online_account[i] = p->account;
			p = p->next;
			i++;
		}
		msg_info.online_num = count;
		msg_info.state = SEEK_OK;
	}
	write(TNode.connfd,&msg_info,sizeof(msg_info));
}

void forbid_say(struct thread_node TNode)  //禁言
{
	Online * p = NULL;
	char sql[SQL_SIZE];
	char * errmsg = NULL;
	char ** result = NULL;
	int nrow,ncol;
	int ret;

	p = TNode.head->next;
//	sqlite3_open("chat_database.db",&TNode.db);
	sprintf(sql,"select * from usr_info where account=%d;",msg_info.account);
	ret = sqlite3_get_table(TNode.db,sql,&result,&nrow,&ncol,&errmsg);
	if (SQLITE_OK != ret)
	{
		printf("select account information error!%s",errmsg);
		msg_info.state = FORB_NO;
		return ;
	}
	if (0 == atoi(result[8]))  //当该用户不是vip时
	{
		while (p != NULL && p->account != msg_info.account)
		{
			p = p->next;
		}
		if (NULL == p)
		{
			printf("no this user!\n");
		}
		else
		{
			//将禁言标志插入数据库
			memset(sql,0,SQL_SIZE);
			
			sprintf(sql,"update usr_info set forbid=%d where account=%d;",msg_info.forbid,msg_info.account);
			ret = sqlite3_exec(TNode.db,sql,NULL,NULL,&errmsg);
			if (SQLITE_OK != ret)
			{
				printf("update forbid error!%s",errmsg);
				msg_info.state = FORB_NO;
				return ;
			}
			p->forbid = FORB_OK;
			msg_info.state = FORB_OK;
			strcpy(msg_info.name,p->name);
		}
	}
	else
	{
		printf("VIP用户无权禁言！\n");
		msg_info.forbid = FORB_NO;
		msg_info.state = FORB_NO;
	}
	write(TNode.connfd,&msg_info,sizeof(msg_info));
	sqlite3_free_table(result);
//	sqlite3_close(TNode.db);
}

void cancel_forbid_say(struct thread_node TNode)
{
	Online * p = NULL;
	char sql[SQL_SIZE];
	char * errmsg = NULL;
	char ** result = NULL;
	int nrow,ncol;
	int ret;

	p = TNode.head->next;
//	sqlite3_open("chat_database.db",&TNode.db);
	sprintf(sql,"select * from usr_info where account=%d;",msg_info.account);
	ret = sqlite3_get_table(TNode.db,sql,&result,&nrow,&ncol,&errmsg);
	if (SQLITE_OK != ret)
	{
		printf("select account information error!%s",errmsg);
		msg_info.state = CAN_SAY_NO;
		return ;
	}
	while (p != NULL && p->account != msg_info.account)
	{
		p = p->next;
	}
	if (NULL == p)
	{
		printf("no this user!\n");
	}
	else
	{
		//将解除禁言标志插入数据库
		memset(sql,0,SQL_SIZE);
			
		sprintf(sql,"update usr_info set forbid=%d where account=%d;",msg_info.forbid,msg_info.account);
		ret = sqlite3_exec(TNode.db,sql,NULL,NULL,&errmsg);
		if (SQLITE_OK != ret)
		{
			printf("update cancel forbid error!%s",errmsg);
			msg_info.state = CAN_SAY_NO;
			return ;
		}
		p->forbid = CAN_SAY_OK;
		msg_info.state = CAN_SAY_OK;
		strcpy(msg_info.name,p->name);
	}
	
	write(TNode.connfd,&msg_info,sizeof(msg_info));
	sqlite3_free_table(result);
//	sqlite3_close(TNode.db);
}

void forced_usr_offline(struct thread_node TNode)  //强制下线
{
	Online * p = NULL;
	Online * q = NULL;
	char sql[SQL_SIZE];
	char * errmsg = NULL;
	char ** result = NULL;
	int nrow,ncol;
	int ret;

//	sqlite3_open("chat_database.db",&TNode.db);
	sprintf(sql,"select * from usr_info where account=%d;",msg_info.account);
	ret = sqlite3_get_table(TNode.db,sql,&result,&nrow,&ncol,&errmsg);
	if (SQLITE_OK != ret)
	{
		printf("select account information error!%s",errmsg);
		msg_info.state = FORB_NO;
		return ;
	}
	if (0 == atoi(result[8]))  //当该用户不是vip时
	{
		q = TNode.head;
		p = TNode.head->next;
		while( p != NULL && p->account != msg_info.account)
		{
			q = p;
			p = p->next;
		}
		if (NULL == p)
		{
			printf("Link is empty!\n");
			msg_info.state = KICK_OUT_NO;
			return;
		}
		else
		{
			strcpy(msg_info.name,p->name);
			msg_info.state = FORCE_OFFLINE;
			write(p->connfd,&msg_info,sizeof(msg_info));
			q->next = p->next;
			free(p);
			printf("node had deleted!");
		}
	}
	else
	{
		msg_info.state = KICK_OUT_NO;
		printf("user is vip,offline error!");
		write(TNode.connfd,&msg_info,sizeof(msg_info));
		return;
	}
	msg_info.state = KICK_OUT_OK;
	write(TNode.connfd,&msg_info,sizeof(msg_info));
	sqlite3_free_table(result);
//	sqlite3_close(TNode.db);
}

void trans_file(struct thread_node TNode)
{
	Online * p = NULL;
	int n,m;
	char name[NAME_SIZE];

	p = TNode.head->next;

	while (p != NULL && p->connfd != TNode.connfd) //找到当前选择私聊的客户机套接口
	{
	    p = p->next;
	}
	if (NULL == p)
	{
	    printf("客户机不存在！\n");
	}
	else
	{
		strcpy(msg_info.name,p->name);  //找到自己的昵称
	}

	p = TNode.head->next;
	while (p != NULL && p->account != msg_info.account)
	{
		p = p->next;
	}
	if (NULL == p)
	{
		printf("查无此人！\n");
		msg_info.state = SEND_FILE_NO;
	}
	else
	{
		msg_info.state = RECV_FILE;
		printf("用户%s向%d发送一个文件！\n",msg_info.name,p->account);
		write(p->connfd,&msg_info,sizeof(msg_info));
	}
	msg_info.state = SEND_FILE_OK;
	write(TNode.connfd,&msg_info,sizeof(msg_info));
}

void *work_func(void *arg)
{
	struct thread_node TNode;
	int ret;
	TNode = *((struct thread_node *)arg);

    while(1)
	{
		memset(&msg_info,0,sizeof(msg_info));
		ret = read(TNode.connfd,&msg_info,sizeof(msg_info));
		if (0 == ret)
		{
			printf("client %d had offline!\n",TNode.connfd);
			delete_node(TNode);
			pthread_exit(NULL);
		}
		printf("flag = %d\n",msg_info.flag);
		
		switch (msg_info.flag)
		{
			case 1:  //注册
				reg_usr(TNode);
				break;
			case 2:  //登录
				login_usr(TNode);
				break;
			case 3:   //私聊
				send_to_one(TNode);
				break;
			case 4:    //群聊
				send_to_all(TNode);
				break;
			case 5:    // 注册vip
				reg_vip(TNode);
				break;
			case 6:    //修改密码
				update_password(TNode);
				break;
			case 7:  //查看所有用户
				seek_online(TNode);
				break;
			case 8:  //禁言
				forbid_say(TNode);
				break;
			case 9:  //解除禁言
				cancel_forbid_say(TNode);
				break;
			case 10:  //踢除在线用户
				forced_usr_offline(TNode);
				break;
			case 11: //发送文件
				trans_file(TNode);
				break;
			default :
				printf("flag error!\n");
				pthread_exit(NULL);
				break;
		}

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
    }
	sqlite3_close(db);
	release_link(&head);  //释放链表
	close(listenfd);   //关闭套接口
    return 0;
}
