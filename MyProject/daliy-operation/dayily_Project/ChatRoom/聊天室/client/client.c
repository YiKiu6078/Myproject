/******clinet*******/

#include "myhead.h"

void *read_msg(void *argc);
//void *read_msg2(void *argc);
void display1();
void display2();
void display3();
int back1 = 0;

int main(int argc, char **argv)
{
	//参输入口检查
	if(argc != 2)
	{
		perror("argc");
		return(-1);
	}

	/*1.socket********/
	int socketfd = 0;
	int ret = 0;
	
	struct sockaddr_in sock_server = {0};

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
	sock_server.sin_addr.s_addr = inet_addr(argv[1]); //绑定IP地址


	/*3.connect*******************************************************************/
	ret = connect(socketfd,(struct sockaddr*)&sock_server,sizeof(struct sockaddr));
	if(ret == -1)
	{
		perror("connect");
		return(-1);
	}
	printf(GREEN"连接端口成功...\n");
	printf(DEFAULT);
	

	//客户端数据输入暂存
	int sendcnt = 0;
	int action = 0;
	int toid = 0;
	char sendbuff[20]={0};
	
	char name[20] = {0};
	char key[20] = {0};
	char keyy[20] = {0};
	char id[20] = {0};
	
	


	//封包结构体
	struct message Msg = {0};
	pthread_t th = 0;

	while(1)
	{
		if(pthread_create(&th,NULL,read_msg,&socketfd) != 0)
		{
			perror("Client:pthread_create");
			return(-1);
		}
		
		
		//printf("接收后back1=%d\n",back1);

		
		//1.输入数据
		printf(GREEN"\n正在进入聊天室loading......\n");
		printf(DEFAULT);
		display1();
		printf("请输入命令：（1.注册;2登录;3.忘记密码;0.退出）\n");
		scanf("%d",&action);
		while((action<0)||(action>3))
		{
			printf(RED"请输入正确的命令：（1.注册;2登录;3.忘记密码;0.退出）\n");//3需要变成5
			printf(DEFAULT);
			scanf("%d",&action);		
		}
		getchar();

		/* if(action == 1)
		{
			printf(GREEN"\n欢迎使用私聊功能：\n");
			printf(DEFAULT);
			
			printf("请输入你接收的对象\n");
			scanf("%d",&toid);
			printf("请输入你要发送的消息");
			scanf("%s",sendbuff);
			//2.数据封包
			Msg.action = action;
			Msg.toid = toid;
			strncpy(Msg.buff,sendbuff,strlen(sendbuff));

			//3.数据发送
			sendcnt = write(socketfd,&Msg,sizeof(struct message));
			if(sendcnt == -1)
			{
				perror("send");
				return(-1);
			}
			else
			{
				printf("您要给server%d发送%d个字节的数据：%s\n",Msg.toid,sendcnt,Msg.buff);
			}

			//	return 0;
		} */
		
		
		if(action == 1)//action要+1,因为服务器端接受的1是私聊任务．Msg.action=1被占用
		{
			action = 2;
			printf(GREEN"\n欢迎进入注册模式：\n");
			printf(DEFAULT);
			
			//printf("%s\n",name);
			strcpy(name,"0");
			strcpy(id,"0");
			strcpy(key,"0");
			//printf("cpy%s\n",name);
			printf("请输入你的昵称：\n");
			//getchar();
			scanf("%s",name);
			//printf("%s\n",name);


			printf("请输入你的密码(20位以内)：\n");
			scanf("%s",key);
		//	printf("%s\n",key);

			while(strlen(key) > 20)
			{
				printf(RED"\n长度溢出！请再次输入密码\n");
				printf(DEFAULT);
				printf("请输入你的密码(20位以内)：\n");
				scanf("%s",key);
			}

			printf("请确认你的密码：\n");
			scanf("%s",keyy);

			while(strcmp(key,keyy) != 0)
			{
				printf(RED"\n两次输入不一致！请再次输入密码\n");
				printf(DEFAULT);
				
				printf("请输入你的密码：\n");
				scanf("%s",key);
				while(strlen(key) > 20)
				{
					printf(RED"\n长度溢出！请再次输入密码\n");
					printf(DEFAULT);
					printf("请输入你的密码(20位以内)：\n");
					scanf("%s",key);
				}
				printf("请确认你的密码：\n");
				scanf("%s",keyy);
			}
			getchar();
	
			//2.数据封包
			Msg.action = action;
			strcpy(Msg.name,name);
		//	printf("fengbao:%s\n",Msg.name);

			strcpy(Msg.key,key);

			sendcnt = write(socketfd,&Msg,sizeof(struct message));
			if(sendcnt == -1)
			{
				perror("send");
				return(-1);
			}
			else
			{
				printf("您要给server发送%d个字节的数据：name:%s  key:%s\n",sendcnt,Msg.name,Msg.key);
			}




/*			//3.服务器进行数据回传
			sendcnt = write(socketfd,&Msg,sizeof(Msg));
			if(sendcnt != -1)
			{
				printf(GREEN"%d注册成功！\n",fromid);
				printf(DEFAULT);
			}
*/
		}
		
		else if(action == 2)//action要+1
		{
			action = 3;
			printf(GREEN"\n欢迎进入登录模式：\n");
			printf(DEFAULT);
		
			strcpy(name,"0");
			strcpy(id,"0");
			strcpy(key,"0");
			
			printf("请输入你的id：\n");
			scanf("%s",id);
			printf("请输入你的密码：\n");
			scanf("%s",key);
			getchar();
			
			//2.数据封包
			Msg.action = action;
			strcpy(Msg.id,id);
			strcpy(Msg.key,key);

			sendcnt = write(socketfd,&Msg,sizeof(struct message));
			if(sendcnt == -1)
			{
				perror("send");
				return(-1);
			}
			else
			{
				printf("您要给server发送%d个字节的数据：id:%s  key:%s\n",sendcnt,Msg.id,Msg.key);
			}
			
			//服务器需要一个遍历链表来确定id已上线,这个遍历加在服务器转发消息的时候

			sleep(1);
			printf("back1=%d\n",back1);
			while(back1 == 1)
			{
				if(atoi(Msg.id) != 1)
				{
				
					int od = 0;
					display2();
					printf("请输入命令：（1.私聊 2.群聊 0.退出）\n");
					scanf("%d",&od);
					while((od<0)||(od>2))
					{
						printf(RED"请输入正确的命令：（1.私聊 2.群聊 0.退出）\n");
						printf(DEFAULT);
						scanf("%d",&od);		
					}
					getchar();
			
				
					if(od == 1)
					{
						
						onechat(socketfd,Msg);
					}
					else if(od == 2)
					{
						
						allchat(socketfd,Msg);
					}
					else
					{
						struct message Msg = {0};
						Msg.action = 6;
						sendcnt = write(socketfd,&Msg,sizeof(struct message));
						if(sendcnt == -1)
						{
							perror("send");
							return(-1);
						}
						else
						{
							printf("您要给服务器发送命令%d\n",Msg.action);
						}
						
						printf(RED"正在回到首页...\n");
						printf(DEFAULT);				
						break;
					}
				}
				
				if(atoi(Msg.id) == 1)
				{
					char iid[20];
					
					int od = 0;
					display3();
					printf("请输入命令：（1.禁言 2.解除禁言 3.踢人 0.退出）\n");
					scanf("%d",&od);
					while((od<0)||(od>3))
					{
						printf(RED"请输入正确的命令：（1.禁言 2.解除禁言 3.踢人 0.退出）\n");
						printf(DEFAULT);
						scanf("%d",&od);		
					}
					getchar();
					
					if(od == 1)//禁言
					{
						
						strcpy(iid,"0");
						printf(RED"\n请输入你想要禁言的人的id:\n");
						printf(DEFAULT);
						scanf("%s",iid);
						while(atoi(iid) == 1)
						{
							printf(RED"你不可以禁言管理员自己，请输入你想要禁言的人的id:\n");
							printf(DEFAULT);
							scanf("%s",iid);		
						}
						getchar();
						
						
						Msg.action = 7;
						strcpy(Msg.user,iid);
						sendcnt = write(socketfd,&Msg,sizeof(struct message));
						if(sendcnt == -1)
						{
							perror("send");
							return(-1);
						}
						else
						{
							printf("您要给server发送%d个字节的数据：id:%s  key:%s\n",sendcnt,Msg.id,Msg.key);
						}
							
						
					}
					else if(od == 2)//解除禁言
					{
						strcpy(iid,"0");
						printf(GREEN"\n请输入你想要解除禁言的人的id:\n");
						printf(DEFAULT);
						scanf("%s",iid);
						while(atoi(iid) == 1)
						{
							printf(RED"你不需要解除禁言管理员自己，请输入你想要解除禁言的人的id:\n");
							printf(DEFAULT);
							scanf("%s",iid);		
						}
						getchar();
						Msg.action = 8;
						strcpy(Msg.user,iid);
						sendcnt = write(socketfd,&Msg,sizeof(struct message));
						if(sendcnt == -1)
						{
							perror("send");
							return(-1);
						}
						else
						{
							printf("您要给server发送%d个字节的数据：id:%s  key:%s\n",sendcnt,Msg.id,Msg.key);
						}
						
					}
					else if(od == 3)//踢人
					{
						strcpy(iid,"0");
						printf(RED"\n请输入你想要踢出的人的id:\n");
						printf(DEFAULT);
						scanf("%s",iid);
						while(atoi(iid) == 1)
						{
							printf(RED"你不可以踢出管理员自己，请输入你想要踢出的人的id:\n");
							printf(DEFAULT);
							scanf("%s",iid);		
						}
						getchar();
						
						Msg.action = 9;
						strcpy(Msg.user,iid);
						sendcnt = write(socketfd,&Msg,sizeof(struct message));
						if(sendcnt == -1)
						{
							perror("send");
							return(-1);
						}
						else
						{
							printf("您要给server发送%d个字节的数据：id:%s  key:%s\n",sendcnt,Msg.id,Msg.key);
						}
						
					}
					else//退出管理员用户
					{
						struct message Msg = {0};
						Msg.action = 6;
						sendcnt = write(socketfd,&Msg,sizeof(struct message));
						if(sendcnt == -1)
						{
							perror("send");
							return(-1);
						}
						else
						{
							printf("您要给服务器发送命令%d\n",Msg.action);
						}
						
						printf(RED"正在回到首页...\n");
						printf(DEFAULT);				
						break;
					}
					
					
					
					
					
				}
			}
			if(back1 != 1)
			{
				printf(RED"密码错误！登录失败");
				printf(DEFAULT);
				continue;
			}
		}

		else if(action == 3)//action要+2
		{
			action = 5;
			printf(GREEN"\n欢迎进入重置密码模式：\n");
			printf(DEFAULT);
			
			strcpy(name,"0");
			strcpy(id,"0");
			strcpy(key,"0");
			//printf("cpy%s\n",name);
			printf("请输入你的ID：\n");
			//getchar();
			scanf("%s",id);
			//printf("%s\n",name);


			printf("重置你的密码(20位以内)：\n");
			scanf("%s",key);
		//	printf("%s\n",key);

			while(strlen(key) > 20)
			{
				printf(RED"\n长度溢出！请再次输入密码\n");
				printf(DEFAULT);
				printf("重置你的密码(20位以内)：\n");
				scanf("%s",key);
			}

			printf("请确认你的密码：\n");
			scanf("%s",keyy);

			while(strcmp(key,keyy) != 0)
			{
				printf(RED"\n两次输入不一致！请再次输入密码\n");
				printf(DEFAULT);
				
				printf("请输入你的密码：\n");
				scanf("%s",key);
				while(strlen(key) > 20)
				{
					printf(RED"\n长度溢出！请再次输入密码\n");
					printf(DEFAULT);
					printf("请重置你的密码(20位以内)：\n");
					scanf("%s",key);
				}
				printf("请确认你的密码：\n");
				scanf("%s",keyy);
			}
			getchar();
	
			//2.数据封包
			Msg.action = action;
		//	printf("fengbao:%s\n",Msg.name);
			strcpy(Msg.id,id);
			strcpy(Msg.key,key);

			sendcnt = write(socketfd,&Msg,sizeof(struct message));
			if(sendcnt == -1)
			{
				perror("send");
				return(-1);
			}
			else
			{
				printf("您要给server发送%d个字节的数据：id:%s  key:%s\n",sendcnt,Msg.id,Msg.key);
			}
	
		}
		
		else
		{
			
			printf(RED"正在退出聊天室waiting......\n");
			sleep(1);
			printf(DEFAULT);
			return 0;
		}
	
	
		/* if(pthread_create(&th,NULL,read_msg,&socketfd) != 0)
		{
			perror("Client:pthread_create");
			return(-1);
		} */
	
	}
}




void *read_msg(void *argc)//来自客户端
{
	int fd = *((int*)argc);
//	printf("fd = %d\n",fd);

	struct message Msg = {0};
	int recvcnt = 0;

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
			printf("客户端%d已关闭\n",fd);
			break;
		}
		else
		{
			//printf("接收后toid=%d,backid=%d,fromid=%d\n",Msg.toid,Msg.backid,Msg.fromid);
			if(Msg.backid == 1)
			{
				back1 = Msg.backid;
				//printf("接收时back1=%d\n",back1);
				break;
			}
			
			if(Msg.toid == 0)
			{
				printf("服务器反馈：%s\n",Msg.buff);
			}	
			else 
			{
			
					printf("用户ID %d 给你发送：%s\n",Msg.fromid,Msg.buff);
			}
		}
		//return NULL;
	}
	return NULL;
}




	

void display1()
{
	sleep(1);
    printf(YELLOW"-------------------------------------------------------------------\n");
    printf(GREEN"|******************请输入您要执行的指令：*************************|\n");
    printf(GREEN"|                                                                 |\n");
	printf(GREEN"|                         1.注册                                  |\n");
    printf(GREEN"|                         2.登录                                  |\n");
    printf(GREEN"|                         3.忘记密码                              |\n");
	printf(RED"|                         0.退出                                  |\n");
    printf(GREEN"|                                                                 |\n");
    printf(YELLOW"|*****************************************************************|\n");
	printf(YELLOW"-------------------------------------------------------------------\n");
	printf(DEFAULT);
}



void display2()
{
	sleep(1);
    printf(YELLOW"-------------------------------------------------------------------\n");
    printf(DEFAULT);
	printf(GREEN"|******************请输入您要执行的指令：*************************|\n");
    printf(GREEN"|                                                                 |\n");
	printf(DEFAULT);
	printf(GREEN"|                         1.私聊                                  |\n");
    printf(GREEN"|                         		                                  |\n");
    printf(GREEN"|                         2.群聊                                  |\n");
    printf(GREEN"|                         		                                  |\n");
	printf(RED"|                         0.退出                                  |\n");
    printf(GREEN"|                                                                 |\n");
    printf(YELLOW"|*****************************************************************|\n");
	printf(YELLOW"-------------------------------------------------------------------\n");
	printf(DEFAULT);
}


void display3()
{
	sleep(1);
    printf(YELLOW"-------------------------------------------------------------------\n");
    printf(DEFAULT);
	printf(GREEN"|************************管理员界面*******************************|\n");
    printf(GREEN"|                                                                 |\n");
	printf(DEFAULT);
	printf(GREEN"|                         1.禁言                                  |\n");
    printf(GREEN"|                         2.解除禁言                              |\n");
    printf(GREEN"|                         3.踢人                                  |\n");
    printf(GREEN"|                         		                                  |\n");
	printf(RED"|                         0.退出                                  |\n");
    printf(GREEN"|                                                                 |\n");
    printf(YELLOW"|*****************************************************************|\n");
	printf(YELLOW"-------------------------------------------------------------------\n");
	printf(DEFAULT);
}




