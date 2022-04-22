#include<stdio.h>
int main()
{
    printf("请输入一个字符：\n");
	char ch;
	scanf("%c",&ch);
	if(ch>='a'&&ch<='z')
	{
	    ch-=32;
		printf("ch=%c\n",ch);
	}
	else if(ch>='A'&&ch<='Z')
	{
	    ch+=32;
		printf("ch=%c\n",ch);
	}
	else if(ch>='0'&& ch<='9')
	{
	    ch -= 48;
		printf("ch=%d\n",ch);
	}
	return 0;
}
