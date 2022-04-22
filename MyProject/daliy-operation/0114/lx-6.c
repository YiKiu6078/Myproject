#include<stdio.h>

int main()
{
	float r,h,c,ys,qs,qv,zv;
	float PI=3.141526;
	printf("请输入半径和高：\n");
	scanf("%f %f",&r,&h);
	c=2*r*PI;
	ys=PI*r*r;
	qs=PI*4*r*r;
	qv=3.0/4.0*PI*r*r*r;
	zv=PI*r*r*h;
	printf("圆的周长是c=%.2f\n",c);
	printf("圆的面积是ys=%.2f\n",ys);
	printf("圆球的面积是qs=%.2f\n",qs);
	printf("圆球的体积是qv=%.2f\n",qv);
	printf("圆柱的体积是zv=%.2f\n",zv);

    return 0;
}
