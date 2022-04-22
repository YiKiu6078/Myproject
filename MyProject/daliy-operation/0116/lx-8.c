#include<stdio.h>

int main()
{
	int num;
	printf("请输入一个不多于5位的正整数：\n");
	scanf("%d",&num);
	while(1)
	{
	    if(num<0||num>99999)
		{
	        printf("你的输入有误！！！\n");
			printf("请输入一个不多于5位的正整数：\n");
	        scanf("%d",&num);
		}
		else
		{
		    break;
		}
	}
	int ge,shi,bai,qian,wan;
    if(num>=10000)
	{
	    printf("5位数\n");
		wan=num/10000;
		qian=num%10000/1000;
		bai=num%1000/100;
		shi=num%100/10;
		ge=num%10;
		printf("%d%d%d%d%d\n",ge,shi,bai,qian,wan);
	}
	else if(num>=1000&&num<=9999)
	{
	    printf("4位数\n");
		qian=num/1000;
		bai=num%1000/100;
		shi=num%100/10;
		ge=num%10;
		printf("%d%d%d%d\n",ge,shi,bai,qian);
	}
	else if(num>=100&&num<=999)
	{
	    printf("3位数\n");
		bai=num/100;
		shi=num%100/10;
		ge=num%10;
		printf("%d%d%d\n",ge,shi,bai);
	}
	else if(num>=10&num<=99)
	{
	    printf("2位数\n");
		shi=num/10;
		ge=num%10;
		printf("%d%d\n",ge,shi);
	}
	else
	{
	    printf("1位数/n");
		ge=num;
		printf("%d\n",ge);
	}
    return 0;
}
