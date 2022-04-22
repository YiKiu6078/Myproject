#include<stdio.h>
int main()
{
   /* printf("请输入一个三位数：\n");
	scanf("%d",&num);*/
	int num,sum;
	int ge,shi,bai;
	//1000以内的水仙花数
    for(num=100;num<1000;num++)
	{
	    
	    ge=num%10;
	    shi=num%100/10;
    	bai=num/100;
        sum=ge*ge*ge+shi*shi*shi+bai*bai*bai;
	    if(sum==num)
	    {
	    printf("%d是水仙花数\n",num);
	    }
	   /* else
	    {
	    printf("%d不是水仙花数\n",num);
	    }*/
	}
	
	//printf("%d是水仙花数\n",num);*/
	
	return 0;
}
