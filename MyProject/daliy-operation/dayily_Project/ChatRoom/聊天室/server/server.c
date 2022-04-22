/******server******/

#include "myhead.h"
char ssid[20];
Node head;
void *read_msg(void *argc);//声明

int main()
{
	online_init(&head);
	printf(GREEN"欢迎使用聊天室，服务器已打开\n");
	printf(DEFAULT);
	int ret = 0;
	int socketfd = 0;
	int clientfd = 0;
	
	pthread_t th = 0;
	
	//保存连接信息
	struct sockaddr_in sock_server = {0};
	struct sockaddr_in sock_client = {0};

	socklen_t len = sizeof(struct sockaddr);
	
	/*1.socket*****************************/
	socketfd = socket(AF_INET,SOCK_STREAM,0);
	if(socketfd == -1)
	{
		perror("socket");
		return(-1);
	}
	printf(GREEN"套接字创建成功...\n");
	printf(DEFAULT);
	
	/*2.bind************************/
	sock_server.sin_family = AF_INET;         //给服务器绑定地址族
	sock_server.sin_port = htons(MYPORT);     //设置服务器端口号
//	sock_server.sin_addr.s_addr = inet_addr(MYADDR);	//给服程序绑定固定IP地址)
	sock_server.sin_addr.s_addr = htonl(INADDR_ANY); //绑定IP地址

	ret = bind(socketfd,(struct sockaddr*)&sock_server,sizeof(struct sockaddr));
	if(ret == -1)
	{
		perror("bind");
		return(-1);
	}
	printf(GREEN"绑定端口成功...\n");
	printf(DEFAULT);


	/*3.listen***************/
	ret = listen(socketfd,10);
	if(ret == -1)
	{
		perror("listen");
		return(-1);
	}
	printf(GREEN"设置监听成功...\n");
	printf(YELLOW"正在等待用户端登录...\n");
	printf(DEFAULT);
	

	printf("sizeof(struct sockaddr) =%ld\n",sizeof(struct sockaddr));
	printf("sizeof(struct sockaddr_in) =%ld\n",sizeof(struct sockaddr_in));


	/*4.accept*/
	while(1)
	{
		clientfd = accept(socketfd,(struct sockaddr*)&sock_client,&len);
		if(clientfd == -1)
		{
			perror("accept");
			return(-1);
		}
		printf(GREEN"接受TCP连接成功...\n");
		printf(DEFAULT);
		printf("clientfd =%d\n",clientfd);
		ret = pthread_create(&th,NULL,read_msg,&clientfd);//传递clientfd; 要知道从哪个客户端来读取数据；
		if(ret != 0)
		{
			perror("pthread_create");
			return(-1);
		}
	}
	close(socketfd);
	return 0;
}


void *read_msg(void *argc)
{
	int fd = *((int*)argc);
	printf("fd = %d\n",fd);  //验证fd是否等于main里的client
	
	
	struct message Msg = {0};
	int recvcnt = 0;
	int sendcnt = 0;
	
	
	
	while(1)
	{
		bzero(&Msg,sizeof(Msg));
		
		//服务器从客户端接收数据
		recvcnt = read(fd,&Msg,sizeof(Msg));
		if(recvcnt < 0)
		{
			perror("recv");
			return NULL;
		}
		else if(recvcnt == 0)
		{
			printf(RED"客户端%d已关闭\n",fd);
			printf(DEFAULT"\n");
			break;
		}
		else
		{
			printf("服务器从客户端%d 接收到数据Msg.buff：%s\n",fd,Msg.buff);
			
			
			if(Msg.action == 1)//发消息
			{
				//Msg.admin = 0;
				//判断禁言标志
				online_send3(head,fd,&Msg);
				online_send1(head,fd,&Msg);
				online_send2(head,fd,&Msg);
				printf("Msg.admin = %d\n",Msg.admin);
				
				if(Msg.admin == 0)
				{
					//服务器进行数据转发
					//printf("发送1前toid=%d,backid=%d,fromid=%d\n",Msg.toid,Msg.backid,Msg.fromid);
					sendcnt = write(Msg.toid,&Msg,sizeof(Msg));
					
					//Msg.toid = 0;
					strcpy(Msg.buff,"发送成功！\n");
					//printf("发送1后toid=%d,backid=%d,fromid=%d\n",Msg.toid,Msg.backid,Msg.fromid);
					sendcnt = write(fd,&Msg,sizeof(Msg));
					//printf("发送2后toid=%d,backid=%d,fromid=%d\n",Msg.toid,Msg.backid,Msg.fromid);
					if(sendcnt != -1)
					{
						printf("服务器向客户端%d 发送了数据：%s\n",Msg.toid,Msg.buff);

					}
				}
				else
				{
					strcpy(Msg.buff,"你被禁言了！\n");
					sendcnt = write(fd,&Msg,sizeof(Msg));
					if(sendcnt != -1)
					{
						printf("服务器向客户端%d 发送了数据：%s\n",Msg.toid,Msg.buff);

					}	
				}
				
				
				
				
			}

			if(Msg.action == 2)//注册
			{
				int id = 0;


				Msg.fromid = fd;
				//服务器进行数据回传	
			//	sendcnt = write(Msg.fromid,&Msg,sizeof(Msg));
								
				reg(id,fd,Msg);  //外调注册函数
				
				
				printf("%s\n",Msg.id);	
				printf("ssidserver%s\n",ssid);	
				
				char suc[50] ="注册成功！你的id为:";
				strcat(suc,ssid);
				strcpy(Msg.buff,suc);
				
				sendcnt = write(fd,&Msg,sizeof(Msg));
				if(sendcnt != -1)
				{
					printf(GREEN"%d注册成功！\n",Msg.fromid);
					printf(DEFAULT);
				}
			

			}
			
			if(Msg.action == 3)//登录
			{
				
				
				int id = 0;
				Msg.fromid = fd;
				//服务器进行数据回传	
			//	sendcnt = write(Msg.fromid,&Msg,sizeof(Msg));
								
				logg(id,fd,Msg,&head);  //外调登录函数
				
		
				printf("登录的IDMsg.id=%s\n",Msg.id);
			

			}
			
			if(Msg.action == 4)//群聊
			{
				//判断禁言标志
				online_send3(head,fd,&Msg);
				
				//这里加一个链表的遍历，先根据fd找一下发送者的id放到Msg.id里
				online_send1(head,fd,&Msg);
				printf("用户%d正在群聊\n",Msg.fromid);
				//再遍历链表，然后把所有在线fd都拿出来发送一遍
				
				if(Msg.admin == 0)
				{
					online_sendall(head,fd,&Msg);
				}
				else
				{
					strcpy(Msg.buff,"你被禁言了！\n");
					sendcnt = write(fd,&Msg,sizeof(Msg));
					if(sendcnt != -1)
					{
						printf("服务器向客户端%d 发送了数据：%s\n",Msg.toid,Msg.buff);

					}	
				}
			}
			
			if(Msg.action == 5)//改密码
			{
				int id = 0;

				Msg.fromid = fd;
				//服务器进行数据回传	
			//	sendcnt = write(Msg.fromid,&Msg,sizeof(Msg));
								
				Mod(id,fd,Msg);  //外调修改函数
				
				
				printf("已完成重置密码的id%s\n",Msg.id);	
				
				char suc[50] ="密码重置成功！用户：";
				strcat(suc,Msg.id);
				strcpy(Msg.buff,suc);
				
				sendcnt = write(fd,&Msg,sizeof(Msg));
				if(sendcnt != -1)
				{
					printf(GREEN"用户%s重置密码成功！\n",Msg.id);
					printf(DEFAULT);
				}
			}
			
			if(Msg.action == 6)//用户下线
			{
				delete_id(&head,fd);
				
			}
			
			if(Msg.action == 7)//用户禁言
			{
				printf("Msg.user = %s\n",Msg.user);
				online_forbid(head,&Msg);
				
			}
			
			if(Msg.action == 8)//用户解除禁言
			{
				printf("Msg.user = %s\n",Msg.user);
				online_allow(head,&Msg);
				
			}
			
			if(Msg.action == 9)//踢人
			{
				Msg.kick = 0;
				/* printf("111Msg.kick=%d\n",Msg.kick); */
				printf("111Msg.user = %s\n",Msg.user);
				
					online_kicked(head,&Msg);
					strcpy(Msg.buff,"警告！！！你已经被踢出在线链表，你的身份被重置为0 \n请输入“0”+ENTER，退出到首页重新登录！！！\n");
					sendcnt = write(Msg.toid,&Msg,sizeof(Msg));
					if(sendcnt != -1)
					{
						printf("服务器向客户端%d 发送了数据：%s\n",Msg.toid,Msg.buff);

					}	
				
				online_kick(head,&Msg);
				/* printf("222Msg.kick=%d\n",Msg.kick); *///kick这里等于1
				printf("222Msg.user = %s\n",Msg.user);
				
				
			
				
				
				
				
			}
			
		}
	}
//	close(fd);

	return NULL;
}

