#include <stdio.h>
#include <stdlib.h>

enum ret_val{EMPTY_OK,EMPTY_NO,};

struct dbl_queue
{
    int num;

	struct dbl_queue * prior,*next;
};

typedef struct dbl_queue Dbl_Queue;
typedef Dbl_Queue * DLqueue;

void create_que_node(DLqueue * queue)
{
    *queue = (DLqueue)malloc(sizeof(Dbl_Queue));
}

void create_queue(DLqueue * queue)
{
    create_que_node(queue);
}

void init_queue(DLqueue queue)
{
    queue->prior = queue->next = queue;
}

int is_empty(DLqueue queue)
{
    if (queue->next == queue || queue->prior == queue)
	{
	    return EMPTY_OK;
	}
	return EMPTY_NO;
}

void push_que_node(DLqueue queue,DLqueue que_node)
{
    que_node->next = queue;
	que_node->prior = queue->prior;
	queue->prior->next = que_node;
	queue->prior = que_node;
}

int pop_que_node(DLqueue queue)
{
	DLqueue p = NULL;
	int num;
	p = queue->next;
    if (EMPTY_OK == is_empty)
	{
	    printf("pop is error!\n");
		return EMPTY_NO;
	}
	else
	{
	    queue->next = p->next;
	    p->next->prior = queue;
	    num = p->num;
	    free(p);
	    return num;
	}
}

int main (int argc,char **argv)
{
    DLqueue queue = NULL;
	DLqueue que_node = NULL;
	int i,num;
	create_queue(&queue);
	init_queue(queue);

	for (i = 0;i < 10;i++)
	{
	    create_que_node(&que_node);
		que_node->num = i + 1;
		push_que_node(queue,que_node);
	}
	for (i = 0;i < 10;i++)
	{
		num = pop_que_node(queue);
	    if (EMPTY_OK == num)
		{
		    printf("pop is error\n");
		}
		else
		{
		    printf("pop is %d\n",num);
		}
	}
	return 0;
}
