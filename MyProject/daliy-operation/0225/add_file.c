#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    FILE *fp1,*fp2,*fp3;
	char ch1,ch2,ch3;

    if (argc != 3)
	{
	    printf("please input fp1 and fp2!\n");
		exit(0);
	}
	fp1 = fopen(argv[1],"r");
	fp2 = fopen(argv[2],"r");
	fp3 = fopen("text3.txt","w");

	while (fp1 == NULL && fp2 == NULL)
	{
	    printf("error!\n");
	}
	while ((ch1 = fgetc(fp1)) != EOF && (ch2 = fgetc(fp2)) != EOF)
	{
	    if (ch1 < '0' || ch1 > '9')
		{
			fputc(ch1,fp3);    
		}
		else 
		{
		    ch1 = ch1 - '0';
			ch2 = ch2 - '0';
			ch3 =( ch1 + ch2) + '0';
			fputc(ch3,fp3);
		}
	}
    
    fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0;
}
