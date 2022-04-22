#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    FILE * from_fd,*to_fd;
	char ch;
    if (argc != 3)
	{
	    printf("need from_fd and to_fd!\n");
		exit(0);
	}
	if ((from_fd = fopen(argv[1],"r")) == NULL)
	{
	    printf("can not find file!!!\n");
		exit(-1);
	}
	ch = fgetc(from_fd);
	if ((to_fd = fopen(argv[2],"w")) == NULL)
	{
	    printf("can not find file!!!\n");
		exit(-1);
	}
	while (ch != EOF)
	{
	    fputc(ch,to_fd);
		ch = fgetc(from_fd);
	}

	fclose(from_fd);
	fclose(to_fd);

	return 0;
}
