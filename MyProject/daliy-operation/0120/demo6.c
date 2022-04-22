#include<stdio.h>
void add(int* p)//每调用一次add函数；num+1;
{
    (*p)++;
}
int main()
{
    int num=0;
	int i;
	for(i=1;i<=5;i++)
	{
		printf("第%d次\n",i);
	    add(&num);
	    printf("num=%d\n",num);
	}
	return 0;
}
