#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

enum return_result{FULL_OK,FULL_NO,EMPTY_OK,EMPTY_NO,PUSH_OK};

struct quece_data
{
    int quece[MAX_SIZE];
	int top;
    int buttom;
};

typedef struct quece_data Quece;

void create_quece(Quece **quece)
{
	
	*quece = (Quece *)malloc(sizeof(struct quece_data));
}

void init_quece(Quece **quece)
{
	(*quece)->top = -1;
    (*quece)->buttom = -1;
}

int is_full(Quece ** quece)
{
    if((*quece)->buttom == -1)
    {
        if((*quece)->top == MAX_SIZE - 1)
            return FULL_OK;
    }
    else if((((*quece)->top - (*quece)->buttom) + 1) == MAX_SIZE) 
		                        //max number is 9 quece is full
	{
        return FULL_OK;
	}

	return FULL_NO;
}

int is_empty(Quece **quece)
{
	if((*quece)->top <= (*quece)->buttom )
	{
		return EMPTY_OK;
	}

	return EMPTY_NO;
}

int push_quece(Quece **quece, int num)
{
    int i ; 
    if(is_full(quece) == FULL_OK)
	 {
		 printf("the quece is full!\n");
		 exit(FULL_OK);
	 }

	 if((*quece)->top < MAX_SIZE - 1)
     {
         ((*quece)->top)++;
    	 ((*quece)->quece[(*quece)->top]) = num;
     }
     else
     {
         for( i = (*quece)->buttom;i <= (*quece)->top; i++)
         {
             (*quece)->quece[i - (*quece)->buttom] = (*quece)->quece[i];
         }
         //(*quece)->top = (*quece)->top - (*quece)->buttom + 1;
         (*quece)->top = (*quece)->top - (*quece)->buttom;
         (*quece)->buttom = 0;
         ((*quece)->top)++;
    	 ((*quece)->quece[(*quece)->top]) = num;
     }
	 return PUSH_OK;
}

int pop_quece(Quece **quece)
{
	if(is_empty(quece) == EMPTY_OK)
	{
		printf("the quece is empty!\n");
		exit(EMPTY_OK);
	}

    return ((*quece)->quece[++((*quece)->buttom)]);
}

int main()
{   
    
	Quece *quece;

    create_quece(&quece);

	init_quece(&quece);

	int i;
    for(i = 0; i < 10; i++)
	{
		if(push_quece(&quece,i+1) == PUSH_OK)
		{
			printf("push num:\t %d\n",i+1);
		}
	}

	for(i = 0; i < 5; i++)
	{
        printf("pop num:\t %d\n",pop_quece(&quece));
	}


    for(i = 0; i < 4; i++) //i = 5 is full max i = 4
	{
		if(push_quece(&quece,i+1) == PUSH_OK)
		{
			printf("push num:\t %d\n",i+1);
		}
	}
	
	for(i = 0; i < 9; i++) //i == 10 is empyty  max  i == 9
	{
        printf("pop num:\t %d\n",pop_quece(&quece));
	}

	return 0;
}
