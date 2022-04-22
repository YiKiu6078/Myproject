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

void menu()  //初始登录注册菜单
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
    printf("\033[0;34m|                         \033[0;36m3.注册vip                              \033[0;34m|\033[0m\n");
    printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m|                        \033[0;31m 0:退出聊天室                           \033[0;34m|\033[0m\n");
    printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m+================================================================+\033[0m\n");
    printf("\n");
}

void function_choice1()  //普通用户功能选择界面
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
    printf("\033[34m |                                    \033[0;36m2:进入群聊\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                    \033[0;36m3:修改密码\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
	printf("\033[34m |                                    \033[0;36m4:发送文件\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                   \033[0;31m0:退出聊天室\033[0;34m                                  |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n"); 
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------|                 |\033[0m\n");
    printf("\033[34m |\033[33m消息输入:\033[0;36m                                                                        \033[34m|                 |\033[0m\n");
    printf("\033[34m +===================================================================================================+\033[0m\n");
   
    printf("\033[9;85H");                       //将光标移到用户名打印位置
    printf("\033[36m\033[1m%s\033[0m \n", name); // 用户名

    printf(" \033[33;12H \033[0;36m"); //将光标移动回到消息发送区
}
 
void function_choice2()  //打印VIP用户功能选择界面
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
    printf("\033[34m |                                    \033[0;36m2:进入群聊\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                    \033[0;36m3:修改密码\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
	printf("\033[34m |                                    \033[0;36m4:发送文件\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                    \033[0;36m5:VIP特权\033[0;34m                                    |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                   \033[0;31m0:退出聊天室\033[0;34m                                  |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n"); 
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------|                 |\033[0m\n");
    printf("\033[34m |\033[33m消息输入:\033[0;36m                                                                        \033[34m|                 |\033[0m\n");
    printf("\033[34m +===================================================================================================+\033[0m\n");
   
    printf("\033[9;85H");                       //将光标移到用户名打印位置
    printf("\033[36m\033[1m%s\033[0m \n", name); // 用户名

    printf(" \033[33;12H \033[0;36m"); //将光标移动回到消息发送区
}

void root_menu()
{
	system("clear");
    printf("\033[1;1H");
    fflush(stdout);
    line = 8;
    frame = 1;
    char name[50];
    printf("\033[34m +===================================================================================================+\033[0m\n");
    printf("\033[34m |                                                                                                   |\033[0m\n");
    printf("\033[34m |\033[35m*********************************************\033[33m\033[1m校园聊天室\033[0;35m********************************************\033[34m|\033[0m\n");
    printf("\033[34m |                                                                                         \033[35m版本:1.0\033[34m  |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------------------------|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------|                 |\033[0m\n");
    printf("\033[34m |                                                                                 |\033[33m\033[1m用户:            \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[33m\033[1m管理员权限：    \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[36m\033[1m0!:在线用户信息  \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
	printf("\033[34m |                                                                                 | \033[36m\033[1m1!:禁言         \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[36m\033[1m2!:解除禁言     \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[36m\033[1m3!:踢人        \033[0;34m |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
	printf("\033[34m |                                                                                 | \033[36m\033[1m4!:退出        \033[0;34m |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[35m输入关键字      \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 | \033[35m进入对应权限    \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------|                 |\033[0m\n");
    printf("\033[34m |\033[33m消息输入:\033[0;36m                                                                        \033[34m|                 |\033[0m\n");
    printf("\033[34m +===================================================================================================+\033[0m\n");

    printf(" \033[9;85H");                       //将光标移到用户名打印位置
    printf("\033[36m\033[1m%s\033[0m \n", msg_info.name); // 用户名

    printf(" \033[33;12H \033[0;36m"); //将光标移动回到消息发送区
}

void reg_usr(int clifd)    //用户注册
{
    int count;
	char name[NAME_SIZE];
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
	char name[NAME_SIZE];
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
			if (msg_info.vip == 1)
			{
				printf("\033[0;31m 检测到您是尊贵的vip用户，\n正在登录，请等待……\033[0m\n");
				msg_info.vip = 1;
				sleep(2);
				printf("\033[0;35m 登录成功！\033[0m\n");
			}
			else
			{
				printf("\033[0;34m 账号密码检测正确,你是普通用户，\n正在登录……\033[0m\n");
				msg_info.vip = 0;
				sleep(2);
				printf("\033[0;35m 登录成功！\033[0m\n");
			//	printf("FORB_OK = %d\n",msg_info.forbid);
				if (msg_info.forbid == FORB_OK)
				{
					printf("\033[0;31m由于你处于被禁言状态，不可以参与群聊！\033[0m\n");
				}
			}
			break;
		}
		else
		{
		    printf("\033[0;34m 您输入的账号或密码有误，请重新输入！\033[0m\n");
		}
	}
}

void reg_vip(int clifd)  //注册VIP
{
	int account;
	int select;

	printf("\033[0;34m请问您是否想成为尊贵的VIP用户：\033[0m\n");
	while (1)
	{
		printf("\033[0;31m1、升级为VIP \033[0;34m2、我再想想！\033[0m\n");
		scanf("%d",&select);
		getchar();
		if (1 == select)
		{
			printf("\033[0;34m 请输入成为VIP的账号！\033[0m\n");
			scanf("%d",&account);
			getchar();
			msg_info.account = account;
			printf("\033[0;34m 正在认证账号，请等待……\033[0m\n");
			msg_info.vip = 1;    //vip 标志为1时表示为vip用户；
			msg_info.flag = 5;    //注册vip;
			write(clifd,&msg_info,sizeof(msg_info));
			sleep(1);
			read(clifd,&msg_info,sizeof(msg_info));
			if (1 == msg_info.vip)
			{
				int money;
				printf("\033[0;34m 账号检验正确，请充值500元！\033[0m\n");
				while(1)
				{
					scanf("%d",&money);
					if (500 == money)
					{
						printf("\033[0;31m 充值成功！恭喜您成为尊贵的VIP！\033[0m\n");
						msg_info.vip = 1;
						break;
					}
					else
					{
						printf("\033[0;34m 您的价格有误，请重复付钱!\033[0m");
					}
				}
			}
			else
			{
				printf("\033[0;34m 您的账号不存在，请先注册！\033[0m\n");
			}
			break;
		}
		else if(2 == select)
		{
			printf("\033[0;34m 真的好可惜啊！您损失了一大波福利！\033[0m");
			break;
		}
		else
		{
			printf("\033[0;35m 您的输入有误，请重新选择！\033[0m\n");
		}
	}
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
				login_usr(clifd);  //用户登录
				break;
			case 2:
				reg_usr(clifd);    //注册操作
				break;
			case 3:
				reg_vip(clifd);    //注册VIP
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
    char msg_buf[MSG_SIZE];
	msg_info.flag = 4;    //flag = 4 表示群聊；
	
	printf("\033[0;34m请输入要发送给大家的消息：\033[0m\n");
	fgets(msg_buf,sizeof(msg_buf),stdin);
	strcpy(msg_info.chat_msg,msg_buf);
	write(clifd,&msg_info,sizeof(msg_info));
	
}

void chat_stoo(int clifd)  //私聊功能
{
    int account;
	char msg_buf[MSG_SIZE];
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

void update_password(int clifd)    //修改密码
{
    char password[16];
	char tmp[16];

	msg_info.flag = 6;
	while(1)
	{
		printf("\033[0;34m请输入新的密码：\033[0m\n");
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
	strcpy(msg_info.password,password);
	write(clifd,&msg_info,sizeof(msg_info));
}

void seek_online(int clifd)    //查看所有在线用户
{
	msg_info.flag = 7;
	printf("\033[0;36m 正在查看所有在线用户！请稍等！\033[0m\n");
	write(clifd,&msg_info,sizeof(msg_info));
}

void forbid_say(int clifd)    //禁言
{
	printf("\033[0;34m请输入想要禁言的用户账号！\033[0m\n");
	scanf("%d",&msg_info.account);
	msg_info.forbid = FORB_OK;  //禁言
	msg_info.flag = 8;   //8 表示禁言
	write(clifd,&msg_info,sizeof(msg_info));
}

void cancel_forbid_say(int clifd)   //解除禁言
{
	printf("\033[0;34m请输入想要禁言的用户账号！\033[0m\n");
	scanf("%d",&msg_info.account);
	msg_info.forbid = CAN_SAY_OK;  //解除禁言
	msg_info.flag = 9;   //9 表示解除禁言
	write(clifd,&msg_info,sizeof(msg_info));
}

void forced_usr_offline(int clifd)  //踢人（强制下线）
{
	printf("\033[0;36m请输入想要踢除的用户账号！\033[0m\n");
	scanf("%d",&msg_info.account);
	msg_info.flag = 10;   //10 表示踢人
	write(clifd,&msg_info,sizeof(msg_info));
}

void root_function(int clifd)   //vip特权选择
{
	int select;

	while (1)
	{
		sleep(2);
		root_menu();
		printf("\033[0;34m 请选择特权！\033[0m\n");
		scanf("%d",&select);
		getchar();
		switch (select)
		{
		case 0:
			seek_online(clifd);  //查看所有在线用户
			break;
		case 1:
		    forbid_say(clifd);    //禁言
			break;
		case 2:
			cancel_forbid_say(clifd);    //解除禁言
			break;
		case 3:
			forced_usr_offline(clifd);  //踢人（强制下线）
			break;
		case 4:
			printf("\033[0;34m正在退出哦！请等待……\033[0m\n");
			sleep(1);
			break;
		default :
			printf("\033[0;36m功能选择错误，请重新选择！\033[0m\n");
			break;
		}
		if (4 == select)
		{
			msg_info.vip = 1;
			break;
		}
	}
}

void trans_file(int clifd)    //文件传输
{
	char buff[1024] = {0};
	char ch = 0;
	int i = 0,fd = 0;
	int ret = 0;

	msg_info.flag = 11;  //11表示文件传输
	printf("\033[0;36m 请输入想要发送文件用户的账号！\033[0m\n");
	scanf("%d",&msg_info.account);

	printf("\033[0;34m请输入发送的文件名：\033[0m\n");
	scanf("%s",msg_info.filename);

	fd = open(msg_info.filename,O_RDONLY,S_IRUSR|S_IWUSR);
	if(fd < 0)
	{
		printf("\033[0;31m该文件不存在！\033[0m\n");
		return;
	}
	else
	{
		while(1)          //从文件中读取数据到file数组中
		{
			memset(&ch,0,sizeof(ch));
			ssize_t read_bytes = read(fd,&ch,sizeof(ch));
			if(read_bytes == -1)
			{
				perror("read");
			}
			if(read_bytes == 0)        //读完退出循环
			{
				break;
			}
			msg_info.file[i] = ch;
			i++;
		}
		msg_info.file[i] = '\0';
		ret = write(clifd,&msg_info,sizeof(msg_info));
		if(ret = -1)
		{
			perror("write");
			return;
		}
	}
}

void *w_func(void * arg)
{
    int clifd;
	int choice;
	char writeline[100];

	clifd = *((int *)arg);
	while (1)
	{
		if (msg_info.vip == 1)
		{
			function_choice2();
			memset(&msg_info,0,sizeof(msg_info));
	   	 	printf("\033[0;34m请选择聊天功能\033[0m\n");
			scanf("%d",&choice);
			getchar();
			switch(choice)
			{
			case 1:
				chat_stoo(clifd);  //私聊功能--表示发送聊天内容
				break;
			case 2:
				chat_stoa(clifd);   //群聊功能
				break;
			case 3:
				update_password(clifd);  //修改密码
				break;
			case 4:
				trans_file(clifd);    //文件传输
				break;
			case 5:
				root_function(clifd);    //vip特权
				break;
			case 0:
				printf("\033[0;36m正在退出……\033[0m\n");
				sleep(1);
				exit(-1);
			default :
				printf("\033[0;34m功能选择错误！\033[0m\n");
				break;
			}
		}
		else if (msg_info.vip == 0)
		{
			function_choice1();
			memset(&msg_info,0,sizeof(msg_info));
	   		printf("\033[0;34m请选择聊天功能\033[0m\n");
			scanf("%d",&choice);
			getchar();
			switch(choice)
			{
			case 1:
				chat_stoo(clifd);  //私聊功能--表示发送聊天内容
				break;
			case 2:
				chat_stoa(clifd);   //群聊功能
				break;
			case 3:
				update_password(clifd);  //修改密码
				break;
			case 4:
				trans_file(clifd);    //文件传输
				break;
			case 0:
				printf("\033[0;36m正在退出……\033[0m\n");
				sleep(1);
				exit(-1);
			default :
				printf("\033[0;34m功能选择错误！请重新选择！\033[0m\n");
				break;
			}
		}
	}
}

void *r_func(void * arg)   //读线程
{
    int clifd;
	int choice;
	char readline[100];
	int nread,i;
	clifd = *((int *)arg);
	while(1)
	{
		memset(&msg_info,0,sizeof(msg_info));
        nread = read(clifd,&msg_info,sizeof(msg_info));
		if (0 == nread)
		{
			printf("\033[0;31m服务器已经下线！\033[0m\n");
			pthread_exit(NULL);
		}
		switch (msg_info.state)
		{
			case ONLINE:  //私聊
				printf("\033[0;31m用户%s对你说%s\033[0m\n",msg_info.name,msg_info.chat_msg);
				break;
			case OFFLINE:
				printf("\033[0;31m该用户目前不在线！\033[0m\n");
			case EXIST_OK:  //群聊
				printf("\033[0;31m用户%s对大家说%s\033[0m\n",msg_info.name,msg_info.chat_msg);
				break;
			case EXIST_NO:
				printf("\033[0;31m对不起，当前只有你在线！\033[0m\n");
				break;
			case MSG_NO:
				printf("你已被禁言，无法参加群聊！\n");
				break;
			case CHANGE_OK:  //修改密码
				printf("\033[0;31m密码修改成功，请您重新登录！\033[0m\n");
				sleep(2);
				printf("\033[0;31m正在退出……\033[0m\n");
				exit(0);
				break;
			case CHANGE_NO:  
				printf("\033[0;31m密码修改失败！\033[0m\n");
				break;
			case SEEK_OK:
				printf("\033[0;36m当前在线的人数为%d!\033[0m\n",msg_info.online_num);
				for (i = 0;i < msg_info.online_num;i++)
				{
					printf("\033[0;36m昵称 %s 账号 %d!\033[0m\n",msg_info.online_name[i],msg_info.online_account[i]);
				}
				break;
			case FORB_OK:  //禁言成功
				printf("\033[0;34m您已成功将用户%s禁言！\033[0m\n",msg_info.name);
				break;
			case FORB_NO:  
				printf("\033[0;31m用户%s是vip用户，不可禁言！\033[0m\n",msg_info.name);
				break;
			case CAN_SAY_OK: //解除禁言成功
				printf("\033[0;31m用户%s已成功解除禁言！\033[0m\n",msg_info.name);
				break;
			case CAN_SAY_NO: //解除禁言error
				printf("\033[0;31m解除禁言失败！\033[0m\n");
				break;
			case KICK_OUT_OK:  //踢除成功
				printf("\033[0;31m用户%s已经被踢除聊天室！\033[0m\n",msg_info.name);
				break;
			case KICK_OUT_NO:
				printf("\033[0;31m踢除用户失败！\033[0m\n");
				break;
			case FORCE_OFFLINE:
				printf("\033[0;31m你可能得罪vip用户了^~^，将被强制下线\033[0m\n");
				sleep(1);
				printf("\033[0;31m你被强制下线！\033[0m\n");
				exit(0);
				break;
			case SEND_FILE_OK:
				printf("\033[0;36m文件发送成功！\033[0m\n");
				break;
			case SEND_FILE_NO:
				printf("\033[0;36m文件发送失败！\033[0m\n");
				break;
			case RECV_FILE:    //接收文件
				{
					char ch = '0';
					int ret = 0;				
					printf("\033[0;31m用户%s发了一个文件给你:\033[0m\n",msg_info.name);
					printf("\033[0;36m文件名是:%s\n文件内容是\033[0m\n",msg_info.filename);
					int fd = 0;
					fd = open("new.txt",O_CREAT|O_RDWR|S_IRUSR|S_IWUSR);					
					if(fd < 0)
					{
						perror("打开失败");
					}
					ret = write(fd,msg_info.file,strlen(msg_info.file));//从file数组中提取数据写入文件
					printf("%s\n",msg_info.file);
					if(ret < 0)
					{
						perror("write");
					}
					break;
				}
			default :
				printf("\033[0;31m该用户不在线！\n");
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
