#include<stdio.h>
int main()
{
	printf("请输入两个数字：\n");
	int num1,num2;
	scanf("%d %d",&num1,&num2);
	printf("请输符号：\n");
	char opt;
	scanf(" %c",&opt);
	int result;
/*	switch(opt)
	{
	case '+':
		result=num1+num2;
	    break;
	case '-':
		result=num1-num2;
		break;
	case '*':
		result=num1*num2;
		break;
	case '/':
		result=num1/num2;
		break;
	default:
		printf("error\n");
		return -2;

	}*/
	if('+'==opt)
	{
	    result=num1+num2;
	}
	else if('-'==opt)
	{
	    result=num1-num2;
	}
	else if('*'==opt)
	{
	    result=num1*num2;
	}
	else if('/'==opt)
	{
	    result=num1/num2;
	}
	else
	{
	    printf("error\n");
	}
	printf("%d %c %d=%d\n",num1,opt,num2,result);
    return 0;
}
