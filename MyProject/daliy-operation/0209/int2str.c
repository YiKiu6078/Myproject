#include"int2str.h"

static void reverse_str(char *src)
{
    if (src == NULL)
	{
		return;
	}
	
	char tmp;
	int len = strlen(src);
	int i;
	for (i = 0;i <= len/2;i++)
	{
		tmp = *(src + i);
		*(src + i) = *(src + len - 1 - i);
		*(src + len - 1 - i) = tmp;
	}
	return;
}
char *int2str(int num)
{
    int i = 0;
	static char src[MAX_SIZE];
	while(num != 0)
	{
	   src[i] = num % 10 + '0';
	   num = num / 10;
	   i++;

	}
	src[i] = '\0';
	reverse_str(src);
	return src;
}
