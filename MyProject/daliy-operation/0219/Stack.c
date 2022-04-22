#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10

enum ret_val
{
	MALLOC_OK = 100,MALLOC_NO,CREATE_OK,CREATE_NO,FULL_OK,FULL_NO,EMPTY_OK,EMPTY_NO,PUSH_OK,PUSH_NO,POP_OK,POP_NO
};

struct stack_node
{
	int stack_date[SIZE];
	int top;
};

typedef struct stack_node Stack;

int is_maolloc_ok(Stack * stack)
{
    if (NULL == stack)
	{
	    return MALLOC_NO;
	}
	return MALLOC_OK;
}

int create_stack(Stack ** stack)
{
    *stack = (Stack *)malloc(sizeof(Stack));
	if (MALLOC_OK == is_maolloc_ok(*stack))
	{
	    return CREATE_OK;
	}
	return CREATE_NO;
}

void init_stack(Stack * stack)
{
	stack->top = -1;
}

int is_full(Stack *stack)
{
	if (stack->top >= SIZE - 1)
	{
		return FULL_OK;
	}
	return FULL_NO;
}

int is_empty(Stack * stack)
{
    if (-1 == stack->top)
	{
		return EMPTY_OK;
	}
	return EMPTY_NO;
}

int push_stack(Stack * stack,int num)
{
	if (FULL_NO == is_full(stack))
	{	
		stack->top++;
	    stack->stack_date[stack->top] = num;
		return PUSH_OK;
	}
	return PUSH_NO;
}

int pop_stack(Stack * stack)
{
    if (EMPTY_OK == is_empty(stack))
	{
		printf("stack is empty!\n");
		return POP_NO;
	}
	else 
	{
		int num = stack->stack_date[stack->top];
	    stack->stack_date[(stack->top)--];
		return num;
	}
}

void display_stack(Stack * stack)
{
    if (-1 == stack->top)
	{
	    printf("stack is empty!\n");
	}
	else 
	{
	    printf("%5d\n",stack->stack_date[stack->top]);
	}
}

int main(int argc,char **argv)
{
	Stack * stack = NULL;
	int i,num;

	create_stack(&stack);
	init_stack(stack);//栈初始化；
	printf("start push stack!\n");
	for (i = 0;i < 10; i++)
	{
	    if(PUSH_OK == push_stack(stack,i + 1))
		{
		    printf("push stack ok!\n");
		}
		else
		{
		    printf("push stack is full!\n");
		}
		display_stack(stack);
	}
	printf("***********************\n");
	printf("start pop stack!\n");
	for (i = 0;i < 10;i++)
	{
		num = pop_stack(stack);
		if (POP_NO != num)
		{
			printf("%5d\n",num);
			printf("pop is ok!\n");
		}
		else
		{
		    printf("pop stack fail!\n");
		}
	}
	display_stack(stack);
	free(stack);
	return 0;
}
