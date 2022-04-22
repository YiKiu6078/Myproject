/*
 * main.c
 *
 *  Created on: 2011-7-27
 *      Author:
 */

#include "../../include/myhead.h"
#include<stdio.h>
int main()
{
	int a,b;
	printf("please input a and b:\n");
	scanf("%d%d",&a,&b);
	printf("%d+%d=%d\n",a,b,add(a,b));
	printf("%d-%d=%d\n",a,b,sub(a,b));
	printf("%d*%d=%d\n",a,b,mul(a,b));
	printf("%d/%d=%f\n",a,b,div(a,b));
    return 0;
}

