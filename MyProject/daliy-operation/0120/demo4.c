#include<stdio.h>
int is_leap_year(int x)
{
    if(x%4==0&&x%400!=0||x%400==0)
		return 1;
	else
		return 0;
}
int main()
{
	int year;
	for(year=1000;year<=2022;year++)//打印1000-20221年的闰年；
	{
	    if(1==is_leap_year(year))
			printf("%d年是闰年\n",year);
	}
    return 0;
}
