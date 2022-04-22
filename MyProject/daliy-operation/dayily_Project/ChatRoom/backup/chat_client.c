#include "c_s.h"

typedef struct msg    //创建结构体
{
    int flag;    //标志位：1、注册 2、登录
    int account;  //账号
    char name[20];
    char password[16];
	char chat_msg[50]; //聊天内容；
	int recv_val; //标志为REG_OK时表示注册成功；标志为LOG_OK时表示登录成功；
	int vip;      //
	int state;    //状态信息
}MSG;

MSG msg_info;

void menu()
{
	printf("\033[0;34m+================================================================+\033[0m\n");
    printf("\033[0;34m|                                                                |\033[0m\n");
    printf("\033[0;34m|***********************\033[0;33m欢迎来到校园聊天室\033[0;34m***********************|\033[0m\n");
    printf("\033[0;34m|                                                    　 版本:1.0 |\033[0m\n");
    printf("\033[0;34m|----------------------------------------------------------------|\033[0m\n");
    printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m|                         \033[0;36m1.用户登录        　                   \033[0;34m|\033[0m\n");
    printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m|                         \033[0;36m2.帐号注册                             \033[0;34m|\033[0m\n");
	printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m|                         \033[0;36m2.注册vip                             \033[0;34m|\033[0m\n");
    printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m|                        \033[0;31m 0:退出聊天室                           \033[0;34m|\033[0m\n");
    printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m+================================================================+\033[0m\n");
    printf("\n");
}

void function_choice()  //打印功能选择界面
{
    system("clear");
    line = 8;
    frame = 0;
    char name[50];
    printf("\033[34m +===================================================================================================+\033[0m\n");
    printf("\033[34m |                                                                                                   |\033[0m\n");
    printf("\033[34m |\033[35m*********************************************\033[33m\033[1m校园聊天室\033[0;35m********************************************\033[34m|\033[0m\n");
    printf("\033[34m |                                                                                         \033[35m版本:1.0\033[34m  |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------------------------|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |\033[33m\033[1m用户:            \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                    \033[0;36m1:私聊功能\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                    \033[0;36m2:进入群聊\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
/*  printf("\033[34m |                                    \033[0;36m3:修改密码\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
 */ printf("\033[34m |                                   \033[0;31m0:退出聊天室\033[0;34m                                  |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n"); 
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------|                 |\033[0m\n");
    printf("\033[34m |\033[33m消息输入:\033[0;36m                                                                        \033[34m|                 |\033[0m\n");
    printf("\033[34m |                                                                                 |\033[0;35m输入\033[31mq!\033[0;35m返回本界面\033[0;34m |\n");
    printf("\033[34m +===================================================================================================+\033[0m\n");
   
/*     if (head->root == 1)
    {
        sprintf(name, "%s(管理员)\n", head->name);
    }
    else if (head->root == 2)
    {
        sprintf(name, "%s(VIP)\n", head->name);
    }
    else
    {
        sprintf(name, "%s\n", head->name);
    }
*/  
	sprintf(name,"%s\n",msg_info.name);
    printf(" \033[9;85H");                       //将管标移到用户名打印位置
    printf("\033[36m\033[1m%s\033[0m \n", name); // 用户名

    printf(" \033[33;12H \033[0;36m"); //将光标移动回到消息发送区
}

void reg_usr(int clifd)    //用户注册
{
    int count;
	char name[20];
	char tmp[16];
	char password[16];

	memset(&msg_info,0,sizeof(msg_info));
	msg_info.flag = 1;
	printf("\033[0;34m请输入昵称：\033[0m\n");
	scanf("%s",name);
	getchar();

	while(1)
	{
		printf("\033[0;34m请输入密码：\033[0m\n");
		scanf("%s",password);
		int len = strlen(password);
		if (6 > len || 16 < len)
		{
			printf("\033[0;34m密码长度不符合规范，请重新输入：\033[0m\n");
		}
		else
		{
			printf("\033[0;34m请再次确认密码：\033[0m\n");
			scanf("%s",tmp);
			getchar();
			if (0 == strcmp(password,tmp))
			{
				printf("\033[0;34m两次密码输入正确：\033[0m\n");
				break;
			}
			else
			{
				printf("\033[0;34m两次密码不匹配，请重新输入：\033[0m\n");
			}
		}
		
	}
	strcpy(msg_info.name,name);
	strcpy(msg_info.password,password);
	printf("\033[0;34m正在生成账号，请等待……：\033[0m\n");
	write(clifd,&msg_info,sizeof(msg_info));
	sleep(2);
	memset(&msg_info,0,sizeof(msg_info));
	read(clifd,&msg_info,sizeof(msg_info));
	if(msg_info.recv_val == REG_OK)
	{
		printf("\033[0;31m%d\033[0m\n",msg_info.recv_val);
		printf("\033[0;34m您已成功注册，您的账号为：\033[0m\n");
		printf("\033[0;31m%d\033[0m\n",msg_info.account);
		printf("\033[0;31m请务必牢记！！！\033[0m\n");
	}
	else
	{
	    printf("\033[0;31m注册失败！\n");
		exit(-1);
	}
	
}

void login_usr(int clifd) //用户登录
{
    int count;
	char name[20];
	char tmp[16];
	char password[16];
	memset(&msg_info,0,sizeof(msg_info));
	msg_info.flag = 2;
	while(1)
	{
		printf("\033[0;34m 请输入账号：\033[0m\n");
		scanf("%d",&msg_info.account);
		getchar();
		printf("\033[0;34m 请输入密码：\033[0m\n");
		scanf("%s",password);
		getchar();
		strcpy(msg_info.password,password);
		write(clifd,&msg_info,sizeof(msg_info)); //将需要登陆的账号密码发送给服务器；
		memset(&msg_info,0,sizeof(msg_info));
		int ret = read(clifd,&msg_info,sizeof(msg_info));
		if (-1 == ret)
		{
		    perror("\033[0;31mread error!\033[0m\n");
		}
//		printf("recv_log = %d\n",msg_info.recv_log);
		if (msg_info.recv_val == LOG_OK)
		{
			printf("\033[0;34m 账号密码检测正确,正在登录……\033[0m\n");
			sleep(1);
			printf("\033[0;35m 登录成功！\033[0m\n");
			break;
		}
		else
		{
		    printf("\033[0;34m 您输入的账号或密码有误，请重新输入！\033[0m\n");
		}
	}
}

void reg_vip(int clifd)
{
	printf("\033[0;34m请问您是否想成为尊贵的VIP用户：\033[0m\n");
}


void do_select(int clifd)
{
	int select;
	while (1)
	{
		menu();
 		printf("\033[0;34m请选择：\033[0m\n");
		scanf("%d",&select);
		getchar();
		switch(select)
		{
			case 1:
				login_usr(clifd);  //普通用户登录
				break;
			case 2:
				reg_usr(clifd);    //注册操作
				break;
			case 3:
			//	reg_vip(clifd);    //注册VIP
				break;
			case 0:
				printf("\033[0;34m 正在退出系统，请等待……！\033[0m\n");
				sleep(2);
				exit(-1);
				break;
			default :
				printf("\033[0;34m选择错误，请重新选择！\033[0m\n");
				break;
		}
		if (1 == select)
		{
			break;
		}
	}
}

void chat_stoa(int clifd)  //群聊
{
    char msg_buf[50];
	msg_info.flag = 4;    //flag = 4 表示群聊；
	printf("\033[0;34m请输入要发送给大家的消息：\033[0m\n");
	fgets(msg_buf,sizeof(msg_buf),stdin);
	strcpy(msg_info.chat_msg,msg_buf);
	write(clifd,&msg_info,sizeof(msg_info));
}

void chat_stoo(int clifd)  //私聊功能
{
    int account;
	char msg_buf[50];
	msg_info.flag = 3;    //flag = 3 表示私聊
	printf("\033[0;34m请输入聊天对象的账号：\033[0m\n");
	scanf("%d",&account);
	getchar();
	msg_info.account = account;
	printf("\033[0;34m请输入要说的悄悄话：\033[0m\n");
	fgets(msg_buf,sizeof(msg_buf),stdin);
	strcpy(msg_info.chat_msg,msg_buf);
	write(clifd,&msg_info,sizeof(msg_info));
}

void *w_func(void * arg)
{
    int clifd;
	int choice;
	char writeline[100];

	clifd = *((int *)arg);
	while (1)
	{
		memset(&msg_info,0,sizeof(msg_info));
	    printf("\033[0;34m请选择聊天功能\033[0m\n");
		scanf("%d",&choice);
		getchar();
		switch(choice)
		{
			case 1:
				
				chat_stoo(clifd);  //私聊功能--表示发送聊天内容
//				send(clifd,&msg_info,sizeof(msg_info),0);
				break;
			case 2:
				chat_stoa(clifd);   //群聊功能
//				send(clifd,&msg_info,sizeof(msg_info),0);
				break;
/*			case 3:
				
				break;
*/
			default :
				printf("\033[0;34m功能选择错误！\033[0m\n");
				exit(-1);
				break;
		}
		
	}
}

void *r_func(void * arg)   //读线程
{
    int clifd;
	int choice;
	char readline[100];
	int nread;
	clifd = *((int *)arg);
	while(1)
	{
		memset(&msg_info,0,sizeof(msg_info));
        nread = read(clifd,&msg_info,sizeof(msg_info));

		switch (msg_info.flag)
		{
			case 1:  //注册
			
				break;
			case 3:  //私聊
				if (msg_info.state == ONLINE)
				{
					printf("用户%s对你说%s\n",msg_info.name,msg_info.chat_msg);
				}
				break;
			case 4:  //群聊
				printf("用户%s对大家说%s\n",msg_info.name,msg_info.chat_msg);
				break;
			default :
				printf("该用户不在线！\n");
				break;
		}
	}
	pthread_exit(NULL);
}

int main(int argc,char **argv)
{
    pthread_t r_tid,w_tid;
//	socklen_t len;
	int ret;
	int clifd;
	MSG msg_info;
	struct sockaddr_in servaddr,cliaddr;

	if (argc != 2)
	{
		printf("need server IP address!\n");
		exit(0);
	}

	clifd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVPORT);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	ret = connect(clifd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if (ret == -1)
	{
		printf("connect error!\n");
		exit(-1);
	}
	do_select(clifd);//登录和注册

	function_choice();
	ret = pthread_create(&w_tid,NULL,(void *)w_func,(void *)&clifd);  //创建写线程
	if (ret == -1)
	{
	    printf("create write thread error!\n");
		exit(-1);
	}
#if 1
	ret = pthread_create(&r_tid,NULL,(void *)r_func,(void *)&clifd);  //创建读线程
	if (ret == -1)
	{
	    printf("create read thread error!\n");
		exit(-1);
	}
#endif

	pthread_detach(w_tid);
	pthread_join(r_tid,NULL);
	close(clifd);
	return 0;
}
