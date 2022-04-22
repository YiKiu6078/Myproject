#include<stdio.h>

int main()
{
	int arr[10]={0};
	printf("输入10个数：\n");
	int i,j;
	int sz=sizeof(arr)/sizeof(arr[0]);
	for(i=0;i<sz;i++)
	{
	    scanf("%d",&arr[i]);
	}
    for(i=0;i<sz-1;i++)
	{    int flag=1;
	     for(j=0;j<sz-1-i;j++)
		 {
		     if(arr[j]>arr[j+1])
			 {
			     arr[j]=arr[j]^arr[j+1];
			     arr[j+1]=arr[j]^arr[j+1];
			     arr[j]=arr[j]^arr[j+1];
			     flag=0;
			 }
		 }
		 if(1==flag)
		 {
		     break;
		 }
	}
	for(i=0;i<sz;i++)
	{
	    printf("%d ",arr[i]);
	}
	putchar(10);
    return 0;
}
