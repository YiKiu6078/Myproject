#include<stdio.h>
/*int fac(int x)//普通函数法
{
    int i;
	int ret=1;
	for(i=1;i<=x;i++)
	{
	    ret *=i;
	}
	return ret;
}*/
int fac(int x)
{
    if(x<=1)
		return 1;
	else
		return x*fac(x-1);
}

int main()
{
	int num=0;
	int ret =0;
	printf("please enter num:\n");
	scanf("%d",&num);
	ret=fac(num);
	printf("%d的阶乘是%d：\n",num,ret);
    return 0;
}
