#include<stdio.h>

void f(int c)
{
    int a=0;
	static int b=0;
	a++;
	b++;
	printf("c=%d,a=%d,b=%d\n",c,a,b);
}
void main()
{
    int i;
	for(i=1;i<=3;i++)
		f(i);
}
