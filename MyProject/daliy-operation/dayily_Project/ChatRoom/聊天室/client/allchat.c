#include "myhead.h"


int allchat(int socketfd,struct message Msg)
{
	int sendcnt = 0;
	
	int action = 0;
	int toid = 0;
	char sendbuff[20]={0};
	
	char name[20] = {0};
	char key[20] = {0};
	char id[20] = {0};
		
		
	{
		printf(GREEN"\n欢迎使用群发功能：\n");
		printf(DEFAULT);
			
		
		printf("请输入你要发送的消息");
		scanf("%s",sendbuff);
		
		
		//2.数据封包
		action = 4;
		Msg.action = action;
		
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
			printf("您要给服务器发送%d个字节的数据：%s\n",sendcnt,Msg.buff);
		}

	}		
		
//	    return 0;
}


