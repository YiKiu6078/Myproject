#include <stdio.h>
#include <stdlib.h>

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

void init_OPND_stack(OPND *stack)
{
	stack->top = -1;
}

void init_OPCH_stack(OPCH *stack)
{
	stack->top = -1;
}

int is_empty_OPND(OPND *stack)
{
	if(stack->top == -1)
	{
		return -1;
	}

	return 0;
}

int is_empty_OPCH(OPCH *stack)
{
	if(stack->top == -1)
	{
		return -1;
	}

	return 0;
}

int get_OPND_top(OPND *stack)
{
	if(is_empty_OPND(stack) == -1)
	{
		return -1;
	}

	return stack->data[stack->top];
}

char  get_OPCH_top(OPCH *stack)
{
	if(is_empty_OPCH(stack) == -1)
	{
		return -1;
	}

	return stack->data[stack->top];
}

void  push_OPND(OPND *stack, int num)
{
    stack->data[++(stack->top)] = num;
	printf("push %d\n",stack->data[stack->top]);
}

void  push_OPCH(OPCH *stack, char ch)
{
    stack->data[++(stack->top)] = ch;
}

int pop_OPND(OPND *stack)
{
	if(is_empty_OPND(stack) == -1)
	{
		return -1;
	}
    
	int num = stack->data[stack->top];

	(stack->top)--;

	return num;
} 

char pop_OPCH(OPCH *stack)
{
	if(is_empty_OPCH(stack) == -1)
	{
		return -1;
	}
    
	char ch = stack->data[stack->top];

	(stack->top)--;

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
	if(get_priority(op_ch) >= get_priority(ch))
	{
		return 1;
	}
	
	return -1;
}

int count(int a, int b, char ch)
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
		
		case '/':
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
	int result_cal;
	OPND * opnd_stack;
	OPCH * opch_stack;

	opnd_stack = (OPND *)malloc(sizeof(OPND));
	opch_stack = (OPCH *)malloc(sizeof(OPCH));

    init_OPND_stack(opnd_stack);
	init_OPCH_stack(opch_stack);

	while((ch = getchar()) != '\n')
	{
        if(ch >= '0' && ch <= '9')
		{
           // push_stack1();
		   opr_num = ch - '0';

		   push_OPND(opnd_stack,opr_num);
		}
        else
		{
			if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
	    	{
		    	//op_ch = pop_stack2();
			  do
			  {

			  		op_ch = get_OPCH_top(opch_stack);

	    	    	if(op_ch == -1)
		        	{
	    	    		push_OPCH(opch_stack,ch);
						break;
	    	    	}
	    	    	else
	    	    	{
	    	        	if(compare_priority(op_ch,ch) < 0)
		            	{
		                	//	push_stack2(ch);
			        	    push_OPCH(opch_stack,ch);
							break;
		            	}
		            	else
		            	{
			         		a = pop_OPND(opnd_stack);
			        		b = pop_OPND(opnd_stack);
							op_ch = pop_OPCH(opch_stack);
							if(a == -1 || b == -1 || op_ch == -1)
							{
								printf("stack is empty!\n");
							}
						//	printf("%d%c%d",a,op_ch,b);
						//	printf("\n");
		            		result_cal = count(b,a,op_ch);
		    		    	push_OPND(opnd_stack,result_cal);
		             	}
					}
		    	}while(compare_priority(op_ch,ch) > 0);
			//  push_OPCH(opch_stack,ch);
		}
	}
	}
	while(is_empty_OPND(opnd_stack) != -1 && is_empty_OPCH(opch_stack) != -1)
	{
	    a = pop_OPND(opnd_stack);
    	b = pop_OPND(opnd_stack);
    	op_ch = pop_OPCH(opch_stack);
    	result_cal = count(b,a,op_ch);
		push_OPND(opnd_stack,result_cal);
	}
//	printf("%d%c%d",a,op_ch,b);
//	printf("\n");

	printf("result is %d\n",result_cal);

	free(opnd_stack);
	free(opch_stack);

	return 0;
}
