#include<stdio.h>
//函数的嵌套调用！！！
//
void new_line()
{
    printf("我只能呵呵了！！！\n");
}
void there_line()
{
    int i;
	for(i=0;i<3;i++)
	{
	    new_line();
	}
}
int main()
{
    there_line();
	putchar('\n');
	printf("%d\n",printf("%d",printf("%d",256)));
	return 0;
}
