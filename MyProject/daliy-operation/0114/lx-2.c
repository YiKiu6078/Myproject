#include<stdio.h>
int main()
{

    int a,b,c,max;
	printf("请输入三个数：\n");
    scanf("%d %d %d",&a,&b,&c);
	int i;
	/*for(i=0;i<3;i++)
	{
	    
	}*/
/*	if(a>b)
    {
	    max=a;
	}
	else
	{
	    max=b;
	}
	if(c>max)
	{
	    max=c;
	}*/
	if(a>b&&a>c)
	{
	    max=a;
		if(b>c)
		{
		    printf("从大到小顺序是%d%d%d\n",a,b,c);
		}
	    else
	    {	
	        if(b>a&&b>c)
		        max=b;
	            if(a>c)
		        {
		            printf("从大到小顺序是%d%d%d\n",b,a,c);
		        }
		        else
		        {
	                if(c>max)
	                {
	                    max=c;
		                if(a>b)
		                {
		                    printf("从大到小顺序是%d%d%d\n",c,a,b);
		                }
	                }
		        }
	    }
	}
	printf("三个数中最大的数是:%d\n",max);
	return 0;
}
