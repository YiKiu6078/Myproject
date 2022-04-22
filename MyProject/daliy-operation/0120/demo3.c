#include<stdio.h>
#include<math.h>
int is_prme(int a)
{
    int b;
	for(b=2;b<sqrt(a);b++)
	{
	    if(0==a%b)
			return a= 0;
	}
	return  a=1;
}
int main()
{
	int i;
	for(i=100;i<=200;i++)
	{
	    if(1==is_prme(i))
		{
		    printf("%d\n",i);
		}
	}
	return 0;
}
