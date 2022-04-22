#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 100

int read_line(int fd, char *buf, int count)
{
	int i;
	char ch;

	for(i = 0; i < count; i++)
	{
        if((read(fd,&ch,1)) < 0)
		{
			perror("read error!\n");
			exit(1);
		}

		if(ch == '\n')
		{
             buf[i] = '\0';
			 return i;
		}

		buf[i] = ch;
	}

	buf[i - 1] = '\0';
	
	return count;
}

int main()
{
	int i;
	int fd;
	int w_count;
	int r_count;
	char filename[MAX];

	char r_buf[MAX];
	char w_buf[MAX];

	printf("Please input filename:\n");
	scanf("%s",filename);

	if((fd = open(filename, O_CREAT | O_RDWR, 0755)) < 0)
	{
		perror("open error!\n");
		exit(1);
	}

	
    for(i = 0; i < 3; i++)
	{
        memset(w_buf,0,sizeof(w_buf));
		scanf("%s",w_buf);
		
		if((w_count = write(fd,w_buf,strlen(w_buf))) < 0)
		{
			perror("write error!\n");
			exit(1);
		}
		else
		{
			write(fd,"\n",1);
		}
	}
    
    lseek(fd,0,SEEK_SET);
#if 0
	if((r_count = read(fd,r_buf,sizeof(r_buf))) < 0)
	{
		perror("read error!\n");
		exit(1);
	}
	else
	{
		r_buf[w_count * 3 + 3] = '\0';
		printf("read data: %s\n",r_buf);
	}
#endif

	for(i = 0; i < 3; i++)
	{
        memset(r_buf,0,sizeof(r_buf));
		read_line(fd,r_buf,100);
		printf("read data: %s\n",r_buf);
	}

	close(fd);

	return 0;
}
