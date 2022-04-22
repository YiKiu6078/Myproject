#include<stdio.h>
#include<unistd.h>
int main()
{
    /*while(1)
	{
	    printf("tzz\n");
		sleep(1);
	}*/
/*	int i=10;
	while(i--)
	{
	    printf("tiezz\n");
	}*/
	int sum=0,year=0;
	double price=200;
	while(1)
	{
	    year++;
		sum+=40;
		price=price*(1+0.01);
		if(sum>price)
		{
		    printf("第%d年可以买房\n",year);
			break;
		}
		printf("第%d年买不起房\n",year);
	}
    return 0;
}
