#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>

#define SERVEPORT 9000

int main()
{
    int listenfd,connfd;//定义监听描述符和连接描述符
	int i;
	int recv_n;//接收到的字节数
	socklen_t len;//定义套接口的整形变量
	char buf[100];
	char buffer[100];
	struct sockaddr_in servaddr,cliaddr;//定义服务器地址和客户机地址--类型为ipv4；


	listenfd = socket(AF_INET,SOCK_STREAM,0);//创建监听接口

	//配置
	bzero(&servaddr,sizeof(servaddr));//服务器地址清零
	servaddr.sin_family = AF_INET;//初始IP类型为ipv4;
	servaddr.sin_port = htons(SERVEPORT);//端口号初始化；
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址初始化为所有地址中任意一个地址

	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));//绑定监听接口；

	listen(listenfd,1024);//监听最大接口数为1024将套接口由主动转为被动； 

	//开始连接客户机地址
	while (1)//本循环表示有客户机退出后循环等待连接；
	{
		len = sizeof(cliaddr);
		connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&len);//创建唯一连接——-连接客户机；
		while (1)
		{
			recv_n = recvfrom(connfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,&len);//接收来自客户机的内容
			if (recv_n == 0)//判断客户机是否仍连接，若是客户机退出则跳出循环等待下次客户机连接；
			{
		    	printf("client had quited!\n");
				break;
			}
			buf[recv_n] = '\0';
			printf("******\n");
			printf("%s\n",buf);
			for (i = 0;i < sizeof(buf);i++)//将小写转化为大写；
			{
	    		buffer[i] = toupper(buf[i]);
			}
			printf("%s\n",buffer);

			sendto(connfd,buffer,strlen(buffer),0,(struct sockaddr *)&cliaddr,len);//发送转换后的字符串到客户机；

		}

		close(connfd);//关闭本次退出连接的客户机接口；
	}
	close(listenfd);

	return 0;
}
