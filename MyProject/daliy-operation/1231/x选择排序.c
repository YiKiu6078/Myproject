#include<stdio.h>

int main(int argc,const char *argv[])
{
    int arr[10]={0};
	int n=sizeof(arr)/sizeof(arr[0]);
	printf("请输入%d个int类型数剧",n);
	int i=0;
	for(i=0;i<n;i++)
	{
	    scanf("%d",arr[i]);

	}
	int m=0;
	for(m=0,m<n-1;m++)
	{
	    int min=m;
		int j=min+1;
		for(;j<n;j++)
		{
		    if(arr[min]>arr[i])
			{
			    min=j;
			}
		}
		if(m!=min)
		{
		    int tmp=arr[m];
			arr[m]=arr[min];
			arr[min]=tmp;
		}
	}
	for(i=0;i<n;i++)
	{
	    printf("%d",arr[i]);
	}
	printf("\n");
    return 0;
}
