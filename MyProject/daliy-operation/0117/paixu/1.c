#include<stdio.h>

int main()
{
	int num1,num2,num3,num4;
	printf("请输入4个整数:\n");
	scanf("%d%d%d%d",&num1,&num2,&num3,&num4);
	int tmp;
    if(num1<num2)
	{
	    tmp=num1;
		num1=num2;
		num2=tmp;
	}
    if(num1<num3)
	{
	    tmp=num1;
		num1=num3;
		num3=tmp;
	}
    if(num1<num4)
	{
	    tmp=num1;
		num1=num4;
		num4=tmp;
	}
    if(num2<num3)
	{
	    tmp=num2;
		num2=num3;
		num3=tmp;
	}
    if(num2<num4)
	{
	    tmp=num2;
		num2=num4;
		num4=tmp;
	}
    if(num3<num4)
	{
	    tmp=num3;
		num3=num4;
		num4=tmp;
	}
	printf("%d>%d>%d>%d\n",num1,num2,num3,num4);
    return 0;
}
