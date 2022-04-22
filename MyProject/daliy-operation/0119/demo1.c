#include<stdio.h>

int main()
{
	int i,j;
	printf("    |");
	for(i=1;i<=9;i++)
	{
	    printf("%4d",i);
	}
	putchar('\n');
	for(i=1;i<=10;i++)
	{
	    printf("----");
	}
	putchar('\n');
	for(i=1;i<=9;i++)
    {
	    printf("%4d|",i);
		for(j=1;j<i;j++)
		{
		    printf("    ");
		}
		for(j=i;j<10;j++)
		{
		    printf("%4d",i*j);
		}
        printf("\n");
	}
	
    return 0;
}
