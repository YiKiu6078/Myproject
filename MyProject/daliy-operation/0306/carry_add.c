#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char ** argv)
{
    FILE * fp1,* fp2,*fp3;
    char ch1,ch2,ch3;
	int count;
	char decade_c,units_c;

	if (argc != 3)
	{
	    printf("please input fp1 and fp2!");
	}

	fp1 = fopen(argv[1],"r");
	fp2 = fopen(argv[2],"r");
	fp3 = fopen("text3.txt","w");

	while (fp1 == NULL && fp2 == NULL)
	{
	    printf("error!\n");
		exit(-1);
	}
    
	while ((ch1 = fgetc(fp1)) != EOF && (ch2 = fgetc(fp2)) != EOF)
	{
	    int sum = 0;
		if (ch1 >= '0' && ch1 <= '9')
		{
		    while (ch1 >= '0' && ch1 <= '9')
			{
			   count = ch1 - '0' + ch2 - '0';
			   sum = sum * 10 + count;
			   ch1 = fgetc(fp1);
			   ch2 = fgetc(fp2);
			}
			decade_c = (sum / 10) + '0';
			units_c = (sum % 10) + '0';
			fputc(decade_c,fp3);
			fputc(units_c,fp3);
		}
		fputc(ch1,fp3);
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0;
}

