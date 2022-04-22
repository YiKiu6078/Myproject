/*****************************************************
copyright (C), 2014-2015, Lighting Studio. Co.,     Ltd. 
File name：
Author：Jerey_Jobs    Version:0.1    Date: 
Description：
Funcion List: 
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int num;
	char name[20];
	struct node *next;
};

struct node_stack
{
	int num;
	char name[20];
};

typedef struct node * Link;
typedef struct node_stack Stack;

enum result {MALLOC_OK = 100,MALLOC_NO,EMPTY_OK,EMPTY_NO,PUSH_OK,PUSH_NO,POP_NO,POP_OK};

int  create_node(Link * new_node)
{
	*new_node = (Link)malloc(sizeof(struct node));

	if(*new_node == NULL)
	{
		printf("malloc error!\n");
	    return MALLOC_NO;
	}
	return MALLOC_OK;
}

void create_stack(Link *stack)
{
	int ret;
	
	ret = create_node(stack);

	if(ret == MALLOC_NO)
	{
		printf("create stack fail!\n");
		exit(-1);
	}
	(*stack)->next = NULL;
}

int push_stack(Link stack,Stack node)
{
	Link new_node;
	int ret;

	ret = create_node(&new_node);

	if(ret == MALLOC_NO)
	{
		printf("push error!\n");
		return PUSH_NO;
	}

	new_node->num = node.num;
	strcpy(new_node->name,node.name);

	new_node->next = stack->next;
	stack->next = new_node;

	return PUSH_OK;
}

int is_empty(Link stack)
{
	if(stack->next == NULL)
	{
		printf("stack is empty!\n");
		return EMPTY_OK;
	}
    return EMPTY_NO;
}

int pop_stack(Link stack,Stack * node)
{
	Link p;
    
	p = stack->next;

	if(is_empty(stack) == EMPTY_OK)
	{
        return POP_NO;
	}
	else
	{
        node->num = p->num;
		strcpy(node->name,p->name);

        stack->next = p->next;
		free(p);
		return POP_OK;
	}
}

int main()
{
	Link stack;
	Stack node;
	int i;
	int ret;
	
	create_stack(&stack);

 	for(i = 0;i < 5; i++)
	{
        node.num = i + 1;
		scanf("%s",node.name);

		push_stack(stack,node);
	}

	for(i = 0; i < 5;i++)
	{
		ret = pop_stack(stack,&node);

		if(ret == POP_NO)
		{
			printf("POP fail!\n");
		}
		else
		{
			printf("num = %d\n",node.num);
			printf("name is :%s\n",node.name);
		}
	}

    return 0;
}
