#include<stdio.h>
#include<string.h>
//get_max函数体
int get_max(int x,int y)
{
    if(x>y)
		return x;
	else
		return y;
}
int main()
{
/*	char arr[]="hello world!"
	memset(arr,'#',5);
	printf("%s\n",arr);*/
	int a,b;
	printf("please enter a and b:\n");
	scanf("%d%d",&a,&b);
	int max=get_max(a,b);
	printf("max=%d\n",max);
	max=get_max(12,b);
	printf("max=%d\n",max);
    return 0;
}
