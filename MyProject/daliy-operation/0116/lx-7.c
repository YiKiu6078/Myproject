#include<stdio.h>

int main()
{
	int grade;
	printf("Please input grade:\n");
	scanf("%d",&grade);
	while(1)
	{
	    if(grade>100||grade<0)
	    {
	        printf("Please enter within 100:\n");
			scanf("%d",&grade);
	    }
	    else
	    {
	        break;
	    }
	}
	if(grade>=90)
	{
	    printf("grade='A'\n");
	}
	else if(grade<=89&&grade>=80)
	{
	    printf("grade='B'\n"); 
	}
	else if(grade<=79&&grade>=70)
	{
	    printf("grade='C'\n"); 
	}
	else if(grade<=69&&grade>60)
	{
	    printf("grade='D'\n"); 
	}
	else
	{
	    printf("grade='E'\n");
	}
    return 0;
}
