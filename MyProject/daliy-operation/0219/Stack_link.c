#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 5

enum ret_val
{
    MALLOC_OK = 100,MALLOC_NO,FULL_OK,FULL_NO,EMPTY_OK,EMPTY_NO,PUSH_OK,PUSH_NO,POP_OK,POP_NO
};

struct link_stack
{
    int num;
    char name[SIZE];

	struct link_stack *next;
};

struct stack_node
{
    int num;
	char name[SIZE];
};

typedef struct link_stack * Link_Stack;
typedef struct stack_node Stack_Node;

int is_malloc_ok(Link_Stack new_node)
{
    if (new_node == NULL)
	{
	    return MALLOC_NO;
	}
	return MALLOC_OK;
}

int create_ls_node(Link_Stack * new_node)
{
	*new_node =  (Link_Stack)malloc(sizeof(struct link_stack));
    if (MALLOC_OK == is_malloc_ok(*new_node))
	{
	    return MALLOC_OK;
	}
	return MALLOC_NO;
}

void create_link_stack( Link_Stack * stack)
{
    create_ls_node(stack);//创建stack为头结点；
	(*stack)->next = NULL;
}


int is_empty(Link_Stack stack)
{
    if (stack->next == NULL)
	{
	    return EMPTY_OK;
	}
	return EMPTY_NO;
}


int push_link_stack(Link_Stack stack,Stack_Node s_node)
{
    Link_Stack new_node = NULL;
    int ret = create_ls_node(&new_node); 
	if (MALLOC_NO == ret)
	{
	    printf("push stack error!\n");
		return PUSH_NO;
	}
		new_node->num = s_node.num;
		strcpy(new_node->name,s_node.name);
	    new_node->next = stack->next;
		stack->next = new_node;
		return PUSH_OK;
}

int pop_link_stack(Link_Stack stack, Stack_Node * s_node)
{
    Link_Stack new_node = NULL;
	new_node = stack->next;
	int ret = is_empty(stack);
	if (EMPTY_OK == ret)
	{
	    printf("pop is error!\n");
		return POP_NO;
	}
	s_node->num = new_node->num;
	strcpy(s_node->name,new_node->name);
	stack->next = new_node->next;
	free(new_node);
	return POP_OK;
}

void display_link_stack(Link_Stack stack)
{
    Link_Stack p = NULL;
	p = stack->next;
	while (p != NULL)
	{
		printf("%d\n",p->num);
		printf("%s\n",p->name);
	    p = p->next;
	}
}

int main(int argc,char **argv)
{
    Link_Stack stack = NULL;
	Stack_Node s_node;
    int i,num;

	create_link_stack(&stack);

	for (i = 0;i < SIZE;i++)
	{
	    s_node.num = i + 1;
	    printf("input name!\n");
		scanf("%s",s_node.name);
		if (PUSH_NO == push_link_stack(stack,s_node))
		{
		    printf("push stack is fail!\n");
		}
		else
		{
		    printf("push stack is ok!\n");
		/*	printf("%d\n",stack->next->num);
			printf("%s\n",stack->next->name);*/
		}
	}
//    display_link_stack(stack);
	for (i = 0;i < SIZE;i++)
	{
	    if (POP_NO == pop_link_stack(stack,&s_node))
		{
		    printf ("stack is empty!\n");
		}
		else
		{
		    printf("num = %d\n",s_node.num);
			printf("name = %s\n",s_node.name);
		}
	}
	return 0;
}
