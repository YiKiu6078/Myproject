#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MALLOC_OK 1
#define MALLOC_NO 0
#define CREATE_OK 1
#define CREATE_NO 0

struct node
{
	int num;

	struct node *next;
};

typedef struct node Node;
typedef Node * Clink;

int is_malloc(Clink new_node)
{
	if (NULL == new_node)
	{
		return MALLOC_NO;
	}
	return MALLOC_OK;
}

int create_new_node(Clink *new_node)
{
	*new_node = (Clink)malloc(sizeof(Node));
	if (MALLOC_OK == is_malloc(*new_node))
	{
		return CREATE_OK;
	}
	return CREATE_NO;
}

int create_clink(Clink * head)
{
	if(CREATE_OK == create_new_node(head))
	{
		(*head)->next = *head;
		return CREATE_OK;
	}
	return CREATE_NO;
}

void insert_node_head(Clink head,Clink new_node)
{
	new_node->next = head->next;
	head->next = new_node;
}

void insert_node_tail(Clink head,Clink new_node)
{
	Clink p = NULL;
	p = head;
	while( p->next != head)
	{
		p = p->next;
	}
	p->next = new_node;
	new_node->next = head;
}

void insert_node_mid(Clink head,Clink new_node,int num)
{
	Clink p = NULL,q = NULL;
	q = head;
	p = head->next;
	while(p != head && p->num != num)
	{
		q = p;
		p = p->next;
	}
	new_node->next = q->next;
	q->next = new_node;
}

void insert_node_sort(Clink head,Clink new_node)
{
	Clink p = NULL,q = NULL;
	q = head;
	p = head->next;
	while(p != head && p->num < new_node->num)
	{
		q = p;
		p = p->next;
	}
	new_node->next = q->next;
	q->next = new_node;
}

void reverse_clink(Clink head)
{
	Clink p1 = NULL,p2 = NULL,p3 = NULL;
	p1 = head->next;
	if(p1 = head)
	{
		return ;
	}
	p2 = p1->next;
	if(p2 == head)
	{
		return ;
	}
	p3 = p2->next;
	while(p3 != head)
	{
	    p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	p2->next = p1;
	head->next->next = head;
	head->next = p2;
}


void display_clink(Clink head)
{
	Clink p = NULL;
	if(NULL == head)
	{
		printf("no this Clink!\n");
		return ;
	}
	else if (head == head->next)
	{
		printf("Clink is empty!\n");
	}
	else
	{
		p = head->next;
		while(p != head)
		{
			printf("%d\n",p->num);
			p = p->next;
		}
	}
}

void seek_node(Clink head,int num)
{
	Clink p = NULL;
	p = head->next;
	while(p != head && p->num != num)
	{
		p = p->next;
	}
	if (p == head)
	{
	    printf("the num is not node_num!\n");
	}
	else
	{
	    printf("find node_num is %d\n",p->num);
	}
}

void delete_node(Clink head,int num)
{
	Clink p = NULL,q = NULL;
	q = head;
	p = head->next;

	while(p != head && p->num != num)
	{
		q = p;
		p = p->next;
	}
	if (p == head)
	{
		printf("the num is not node_num!\n");
	}
	else
	{
		q->next = p->next;
		free(p);
	}
}

int count_node(Clink head,int count)
{
	Clink p = NULL;
	p = head->next;
	while(p != head)
	{
		p = p->next;
		count++;
	}
	return count;
}

void empty_clink(Clink head)
{
	Clink p = NULL;
	p = head->next;
	while(p != head)
	{
		head->next = p->next;
		free(p);
		p = head->next;
	}
}

void release_clink(Clink * head)
{
    empty_clink(*head);
	free(*head);
	*head = NULL;
}

int main(int argc ,char **argv)
{
	Clink head = NULL;
	Clink new_node = NULL;

	srand((unsigned)time(NULL));
	create_clink(&head);
	
	int i,num;
	int count = 0;
	for (i = 0;i < 10;i++)
	{
		if(CREATE_OK == create_new_node(&new_node))
		{
		//	new_node->num = i + 1;
			new_node->num = rand()%100;
			insert_node_head(head,new_node);
		//	insert_node_tail(head,new_node);
		//	insert_node_sort(head,new_node);//死循环了
		}
	}
	printf("insert_node:Clink is:\n");
	display_clink(head);
#if 0	
	printf("please input node_num:\n");
	scanf("%d",&num);

	if(CREATE_OK == create_new_node(&new_node))
	{
		printf("please input your num:\n");
		scanf("%d",&new_node->num);
		insert_node_mid(head,new_node,num);
	}
	printf("insert_node_mid :Clink is:\n");
	display_clink(head);
#endif
	
	printf("please input find num:\n");
	scanf("%d",&num);
	seek_node(head,num);

	reverse_clink(head);
	printf("reverse:Clink is :\n");
	display_clink(head);

	printf("please input delete node_num:\n");
	scanf("%d",&num);
	delete_node(head,num);
	display_clink(head);

	int node_count = count_node(head,count);
	printf("the quantity of node is %d\n",node_count);
#if 1
	empty_clink(head);
	printf("empty:Clink is:\n");
	display_clink(head);

	release_clink(&head);
	printf("release:Clink is :\n");
	display_clink(head);
#endif
	return 0;
}
