#include "int2str.h"

int main(int argc, char **argv)
{
    int num;
	printf("Please input num:\n");
	scanf("%d",&num);
	char *result = int2str(num);
	printf("result = %s\n",result);
	
	return 0;
}
