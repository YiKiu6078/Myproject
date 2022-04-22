#include<stdio.h>
int main()
{
	int i,p;
	p=1;
	i=2;
	while(i<5)
	{
	    p=p*i;
		i=i+1;
	}
	printf("%d\n",p);//5的阶乘！
    return 0;
}
