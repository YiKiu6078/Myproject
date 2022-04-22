#include <stdio.h>
#include<stdlib.h>

#define MAX 100

struct operand
{
    int data[MAX];
    int top;
};

struct operator_ch
{
    int top;
    char data[MAX];
};


typedef struct operand OPND;
typedef struct operator_ch OPCH;

void create_OPND_stack(OPND ** stack1)
{
    *stack1 = (OPND *)malloc(sizeof(OPND));
}

void create_OPCH_stack(OPCH ** stack2)
{
    *stack2 = (OPCH *)malloc(sizeof(OPCH));
}

void init_OPND_stack(OPND *stack1)
{
	stack1->top = -1;
}

void init_OPCH_stack(OPCH *stack2)
{
	stack2->top = -1;
}

void is_empty_OPND(OPND *stack1)
{
	if(stack1->top == -1)
	{
		return -1;
	}

	return 0;
}

void is_empty_OPCH(OPCH *stack2)
{
	if(stack2->top == -1)
	{
		return -1;
	}

	return 0;
}

int get_OPND_top(OPND *stack1)
{
	if(is_empty_OPND(stack1) == -1)
	{
		return -1;
	}

	return stack1->data[stack1->top];
}

int get_OPCH_top(OPCH *stack2)
{
	if(is_empty_OPCH(stack2) == -1)
	{
		return -1;
	}

	return stack2->data[stack2->top];
}

int push_OPND(OPND *stack1, int num)
{
    stack1->data[++(stack1->top)] = num;
}

int push_OPCH(OPND *stack2, char ch)
{
    stack2->data[++(stack2->top)] = ch;
}

int pop_OPND(OPND *stack1)
{
	if(is_empty_OPND(stack1) == -1)
	{
		return -1;
	}
    
	int num = stack1->data[stack1->top];

	(stack->top)--;

	return num;
} 

char pop_OPCH(OPCH *stack2)
{
	if(is_empty_OPCH(stack2) == -1)
	{
		return -1;
	}
    
	char ch = stack2->data[stack2->top];

	(stack2->top)--;

	return ch;
} 

int get_priority(char ch)
{
	if(ch == '+' || ch == '-')
	{
		return 1;
	}

	if(ch == '*' || ch == '/')
	{
		return 2;
	}
}

int compare_priority(char op_ch, char ch)
{
	if(get_priority(op_ch) > get_priority(ch))
	{
		return 1;
	}
	
	return -1;
}

int count(int num1, int num2, char ch)
{
    int result;

	switch(ch)
	{
		case '+':
		{
            result = a + b;
			break;
		}

		case '-':
		{
			result = a - b;
			break;
		}
		
		case '*':
		{
			result = a * b;
			break;
		}
		
		case '-':
		{
			result = a / b;
			break;
		}
	}

	return result;
}

int main()
{
    char ch;
	char op_ch;
	int a,b;
	int opr_num;

	OPND *stack1 = NULL;
	OPCH *stack2 = NULL;

	create_OPND_stack(&stack1);
	create_OPCH_stack(&stack2);

	init_OPND_stack(stack1);
	init_OPCH_stack(stack2);

	while((ch = getchar()) != '\n')
	{
        if(ch >= '0' && ch <= '9')
		{
            opr_num = ch - '0';
			push_OPND(stack1,opr_num);
		}

		if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
		{
		    
		/*	op_ch = pop_OPCH(stack2);
			if(compare(op_ch,ch) > 0)
			{
				push_OPCH(ch);
			}
			else
			{
				count(a,b,op_ch);
			}
		*/
		}
	}
	
	return 0;
}
