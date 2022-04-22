#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

enum ret_val{FULL_OK,FULL_NO,EMPTY_OK,EMPTY_NO,PUSH_OK,PUSH_NO,POP_OK,POP_NO};

struct quece_node
{
    int quece[MAX_SIZE];

	int top;
	int buttom;
};

typedef struct quece_node Quece;

void create_quece(Quece ** quece)
{
    *quece = (Quece *)malloc(sizeof(Quece));
}

void init_quece(Quece ** quece)
{
    (*quece)->top = 0;
	(*quece)->buttom = 0;
}

int is_full(Quece ** quece)
{
    if (((*quece)->buttom + 1) % MAX_SIZE == (*quece)->top)
	{
	    return FULL_OK;
	}
	else 
	{
	    return FULL_NO;
	}
}

int is_empty(Quece ** quece)
{
    if ((*quece)->top == (*quece)->buttom)
	{
	    return EMPTY_OK;
	}
	return EMPTY_NO;
}

int push_quece(Quece ** quece,int num)
{
    if (FULL_OK == is_full(quece))
	{
	    return PUSH_NO;
		exit(FULL_OK);
	}
    if (FULL_NO == is_full(quece))
	{
		(*quece)->top++;
	    (*quece)->quece[(*quece)->top] = num;
	}
	return PUSH_OK;
}

int pop_quece(Quece ** quece)
{
    if (EMPTY_OK == is_empty(quece))
	{
	    printf("pop is error!\n");
		exit(POP_NO);
	}
	return (*quece)->quece[++(*quece)->buttom];
}

int main(int argc,char ** argv)
{
    Quece * quece = NULL;
	int i,num;
	create_quece(&quece);
	init_quece(&quece);
	
    for (i = 0;i < MAX_SIZE;i++)
	{
	    if (PUSH_OK == push_quece(&quece,i + 1))
		{
		    printf("push %d is success!\n",i + 1);
		}
	}
    for (i = 0;i < MAX_SIZE; i++)
    {
	    int ret = pop_quece(&quece);
		printf("pop %d is success\n",ret);
	}
	return 0;
}
