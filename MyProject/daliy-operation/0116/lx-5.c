#include<stdio.h>
#include<math.h>
int main()
{
	int a;
	printf("请输入一个小于1000的正数：\n");
	scanf("%d",&a);
	while(1)
	{
	    if(a>=1000||a<0)
	    {
	        printf("请输入一个小于1000的正数：\n");
	        scanf("%d",&a);
	    }
	    else
	    {
		break;
		}
	}
	        int b,c;
	        b=sqrt(a);
		    c=sqrt(a);
		    if(0==b%1)
		    {
		        printf("%d\n",b);
		    }
		   else
		    {
		        printf("%d\n",c);
		    }
//	printf("%.2f\n",b);
    return 0;
}
