#include<stdio.h>
//冒泡排序
void bubble_sore(int arr[],int sz)
{
    int i,j;
	for(i=0;i<sz-1;i++)
	{
		int flag=1;
	    for(j=0;j<sz-1-i;j++)
		{
		    if(arr[j]>arr[j+1])
			{
			    int tmp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=tmp;
			    flag=0;
			}
		}
		if(1==flag)
		{
		    break;            //定义flag为优化函数，若数组本身就是有序则秩序执行一次就可退出
		}
	}
}
int main()
{
	int i;
    int arr[]={3,2,4,9,8,5,10,11,13,19,7};
	int sz=sizeof(arr)/sizeof(arr[0]);
	bubble_sore(arr,sz);
    for(i=0;i<=sz-1;i++)
	{
	    printf("arr[%d]=%d\n",i,arr[i]);
	}
    return 0;
}
