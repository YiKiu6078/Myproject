#include<stdio.h>
int main()
{
	int num;
	printf("***1.注册 2.登录 3.退出***\n");
	printf(">>>");
	scanf("%d",&num);
/*	if(1==num)
	{
	    printf("正在执行注册操作\n");
	}
	else if(2==num)
	{
	    printf("正在执行登录操作\n");
	}
	else if(3==num)
	{
	    printf("正在执行退出操作\n");
	}
	else
	{
	    printf("你的输入有误\n");
	}*/
	switch(num)
	{
	case 1:
		printf("正在执行注册操作\n");
		break;
	case 2:
		printf("正在执行登录操作\n");
		break;
	case 3:
		printf("正在执行退出操作\n");
		break;
	default:
		printf("输入有误请重新输入\n");
		break;
	}
    return 0;
}
