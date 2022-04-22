#include<stdio.h>
int binary_search(int arr[],int num,int sz)//二分查找函数调用
{
    int left=1;
	int right=sz;
	while(left<=right)
	{
	    int mid=(right+left)/2;
	    if(arr[mid]<num)
		{
		    left=mid+1;
		}
		else if(arr[mid]>num)
		{
		    right=mid-1;
		}
		else
		{
		    return mid+1;
		}
	}
	return -1;
}
int main()
{
	int arr[]={1,2,3,4,5,6,7,8,9,10};
	int num;
	printf("please enter num within 10!\n");
	scanf("%d",&num);
	int sz=sizeof(arr)/sizeof(arr[0]);
    int ret=binary_search(arr,num,sz);
    if(-1==ret)
	{
	    printf("sorry not found!!!\n");
	}
	else
	{
	    printf("congratulations!!! is%d\n",ret);
	}
    return 0;
}

