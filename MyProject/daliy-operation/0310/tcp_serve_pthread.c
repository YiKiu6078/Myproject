#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#define SERVEPORT 8000

void * work_pthread(void * arg)
{
	int i,recv_n;
    socklen_t len;
	char buf[100],BUF[100];
	int connfd;
	connfd = *(int *)arg;

	while (1)
	{
		memset(buf,0,sizeof(buf));
		memset(BUF,0,sizeof(BUF));
		recv_n = recvfrom(connfd,buf,sizeof(buf),0,NULL,NULL);
		if (0 == recv_n)
		{
			printf("client had quited!\n");
			break;
		}
		buf[recv_n] = '\0';
		printf("receiv content is %s\n",buf);
		for (i = 0;i < recv_n;i++)
		{
			BUF[i] = toupper( buf[i] );
		}
		printf("change content is %s\n",BUF);
		sendto(connfd,BUF,100,0,NULL,0);
	}
	close(connfd);
	return NULL;

}

int main()
{
//	socklen_t len;
	int listenfd,connfd;
//	pid_t pid;
//	int i,recv_n;
//	char buf[100],BUF[100];
	struct sockaddr_in servaddr,cliaddr;
	pthread_t pid;

	listenfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVEPORT);

	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	listen(listenfd,1024);
	while (1)
	{

//		len = sizeof(cliaddr);
//		connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&levn);
		connfd = accept(listenfd,NULL,NULL);
		pthread_create(&pid,0,work_pthread,(void *)&connfd);

#if 0
		if ((pid = fork()) == 0)
		{
			while (1)
			{
				close(listenfd);
				memset(buf,0,sizeof(buf));
				memset(BUF,0,sizeof(BUF));
				recv_n = recvfrom(connfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,&len);
				if (0 == recv_n)
				{
					printf("client had quited!\n");
					break;
				}
				buf[recv_n] = '\0';
				printf("receiv content is %s\n",buf);
				for (i = 0;i < recv_n;i++)
				{
					BUF[i] = toupper( buf[i] );
				}
				printf("change content is %s\n",BUF);
				sendto(connfd,BUF,100,0,(struct sockaddr *)&cliaddr,len);
			}
			close(connfd);
			exit(1);
		}

#endif
	}
	close(listenfd);
    
	return 0;
}
