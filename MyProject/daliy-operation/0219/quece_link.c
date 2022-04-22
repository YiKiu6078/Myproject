/*****************************************************
copyright (C), 2014-2015, Lighting Studio. Co.,     Ltd. 
File name：
Author：Jerey_Jobs    Version:0.1    Date: 
Description：
Funcion List: 
*****************************************************/

#include <stdio.h>
#include <stdlib.h>

struct dbl_node
{
	int num;

	struct dbl_node *prior;
	struct dbl_node *next;
};

typedef struct dbl_node Dblnode;
typedef Dblnode * Dbllink;

enum return_val{EMPTY_OK = 100,EMPTY_NO,POP_OK,POP_NO};

void create_node(Dbllink * new_node)
{
	*new_node = (Dbllink) malloc(sizeof(Dblnode));
}

void create_quece(Dbllink* quece)
{
	//*quece = (Dbllink)malloc(sizeof(Dblnode));
	create_node(quece);
}

void init_quece(Dbllink quece)
{
	quece->prior = quece->next = quece;
}

void push_quece(Dbllink quece,Dbllink new_node)
{
	new_node->prior = quece->prior;
	new_node->next = quece;
	quece->prior->next = new_node;
	quece->prior = new_node;
}

int is_empty(Dbllink quece)
{
	if(quece->next == quece || quece->prior == quece)
	{
		return EMPTY_OK;
	}
	return EMPTY_NO;
}

int pop_quece(Dbllink quece)
{
	Dbllink p;
	int num;
	p = quece->next;
	if(EMPTY_OK == is_empty(quece))
	{
		printf("quece is empty!\n");
		return POP_NO;
	}
	else
	{
        quece->next = p->next;
		p->next->prior = quece;
        num = p->num;
		free(p);
		return num;
	}
}

int main()
{
	Dbllink quece;
	Dbllink new_node;
	int i;
	int num;

	create_quece(&quece);
	init_quece(quece);

	for(i = 0; i < 10; i++)
	{
		create_node(&new_node);
		new_node->num = i + 1;
		push_quece(quece,new_node);
	}

	for(i = 0; i < 10;i++)
	{
		num = pop_quece(quece);
		
		if( POP_NO == num)
		{
			printf("pop error!\n");
		}
		else
		{
			printf("num = %d\n",num);
		}
	}

    return 0;
}
