#include<stdio.h>

int main()
{
	printf("请输入年份：\n");
	int year;
	scanf("%d",&year);
	if((0==year%4)&&(0!=year%100)||(0==year%400))
	{
	    printf("%d是闰年\n",year);
	}
	else
	{
	    printf("%d是平年\n",year);
	}
    return 0;
}
