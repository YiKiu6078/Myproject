#include <stdio.h>

//int main()
/*
	int a,b,tmp;
	printf("please enter a and b:\n");
	scanf("%d%d",&a,&b);
	*1
	tmp=a;
	a=b;
    b=tmp;
	*2
	a=a+b;
	b=a-b;
	a=a-b;*/
	//3*异或操作
/*	a=a^b;
	b=a^b;
	a=a^b;
	printf("a=%d,b=%d\n",a,b);
    return 0;
}*/
void exchage(int *x,int *y)
//*下方并没有给exchage定义类型，
//所以应该没有返回类型，应为void.int 是error的；
{
    *x=*x^*y;
	*y=*x^*y;
	*x=*x^*y;
}
int main()
{
	int a,b,tmp;
	printf("please enter a and b:\n");
	scanf("%d%d",&a,&b);
	exchage(&a,&b);
	printf("a=%d,b=%d\n",a,b);
}
