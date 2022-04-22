#include<stdio.h>

int main()
{
    int i,j;
	j=1;
	i=2;
	while(i<5)
	{
	    j=j*i;
		i=i+1;
	}
	printf("%d\n",i);
    return 0;
}
