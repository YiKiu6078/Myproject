#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVEPORT 8000

int main()
{
	socklen_t len;
	int sock_serfd;
	int i,recv_n;
	char buf[100],BUF[100];
	struct sockaddr_in servaddr,cliaddr;

	sock_serfd = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVEPORT);

	bind(sock_serfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	while (1)
	{
		len = sizeof(cliaddr);
		memset(buf,0,sizeof(buf));
		memset(BUF,0,sizeof(BUF));
		recv_n = recvfrom(sock_serfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,&len);
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
		sendto(sock_serfd,BUF,100,0,(struct sockaddr *)&cliaddr,len);
	}
	close(sock_serfd);
	return 0;
}
