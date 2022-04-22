#include<stdio.h>


union endian
{
    int n;
	char c;
};
int main()
{
    union endian test;
	test.n=1;
	if(1==test.c)
		printf("little%c\n",test.c);
	else
		printf("big%c\n",test.c);

    return 0;
}
