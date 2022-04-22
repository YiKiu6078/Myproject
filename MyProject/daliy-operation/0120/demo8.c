#include<stdio.h>
//自己写一个测量字符串长度的函数！！！
#include<string.h>
/*int my_strlen(char* str)//内部定义变量count；
{
	int count=0;
    while(*str!='\0')
	{
		count ++;
		str ++;
	}
	return count;
}*/
int my_strlen(char* str)//递归函数法！！！
{
    if(*str !='\0')
		return 1+my_strlen(str+1);
	else
		return 0;

}
int main()
{
	char arr[]="i am going to have a girlfriend";
    int len=my_strlen(arr);
	printf("%s\n",arr);
	printf("共%d个字符\n",len);
	return 0;
}
