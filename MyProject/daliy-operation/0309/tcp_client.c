#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define SERVEPORT 9000   //宏定义端口号：客户机与服务器端口号应相同；

int main(int argc,char **argv)
{
    int clifd;//创建客户机描述符；
	socklen_t len;
	char senline[100];
	char recvline[100];
	int recv_n;//定义recvfrom函数的接收变量；
	struct sockaddr_in servaddr,cliaddr;//定义服务器和客户机的地址；

	if (argc != 2)//在命令行输入IP地址；
	{
	    printf("need ip to connect!");
		exit(-1);
	}
	clifd = socket(AF_INET,SOCK_STREAM,0);//创建客户机套接口；

	bzero(&servaddr,sizeof(servaddr));//进行初始化
	servaddr.sin_family = AF_INET;//初始化类型为IPv4;
	servaddr.sin_port = htons(SERVEPORT);//初始化端口号
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);//初始化IP地址为命令行输入的地址

	connect(clifd,(struct sockaddr *)&servaddr,sizeof(servaddr));//连接服务器地址

	printf("please input send content!\n");
	while (fgets(senline,100,stdin) != NULL)//从键盘循环获取字符串
    {
		len = sizeof(servaddr);
		sendto(clifd,senline,strlen(senline),0,(struct sockaddr *)&servaddr,len);//将字符串发送给服务器；
		printf("*************\n");
		printf("This is receive content!\n");
		recv_n = recvfrom(clifd,recvline,sizeof(recvline),0,NULL,NULL);//接收来自服务器的内容，已经和服务器建立过连接，
																		//所以服务器地址可以为NULL。
		recvline[recv_n] = '\0';//加上字符串结束标志
		fputs(recvline,stdout);//将接收到的内容输出在屏幕上；
	}
	close(clifd);//关闭套接口；

	return 0;
}
