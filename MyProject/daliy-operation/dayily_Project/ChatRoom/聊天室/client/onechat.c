/*******私聊程序*******/

#include "myhead.h"


int onechat(int socketfd,struct message Msg)
{
	int sendcnt = 0;
	
	int action = 0;
	int toid = 0;
	char sendbuff[20]={0};
	
	char name[20] = {0};
	char key[20] = {0};
	char id[20] = {0};
		
		
	{
		printf(GREEN"\n欢迎使用私聊功能：\n");
		printf(DEFAULT);
			
		printf("请输入你接收的对象\n");
		scanf("%d",&toid);
		printf("请输入你要发送的消息");
		scanf("%s",sendbuff);
		
		
		//2.数据封包
		action = 1;
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
			printf("您要给用户%d发送%d个字节的数据：%s\n",Msg.toid,sendcnt,Msg.buff);
		}

	}		
		
//	    return 0;
}













