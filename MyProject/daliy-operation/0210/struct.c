#include<stdio.h>

    struct s
	{
		int a;
		float b;
		double c;
		char arr[100];
	};
int main()
{
	struct s s = {100,3.14,0.521,"zhizhi"};
	printf("%d,%f,%lf,%s\n",s.a,s.b,s.c,s.arr);
	
	return 0;

}
