#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#define SERVEPORT 8000

int main(int argc,char ** argv)
{
	int sock_client;
	socklen_t len;
	int n;
	char sen[100],recv[100];
	struct sockaddr_in servaddr,cliaddr;

	if (argc != 2)
	{
	    printf("need input ip address!\n");
		exit(0);
	}
	sock_client = socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVEPORT);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);

	connect(sock_client,(struct sockaddr *)&servaddr,sizeof(servaddr));

	while (fgets(sen,100,stdin) != NULL)
	{
		len = sizeof(servaddr);
	    sendto(sock_client,sen,strlen(sen),0,(struct sockaddr *)&servaddr,len);

		n = recvfrom(sock_client,recv,100,0,NULL,NULL);
		recv[n] = '\0';
		fputs(recv,stdout);
	}

	close(sock_client);
    return 0;
}
