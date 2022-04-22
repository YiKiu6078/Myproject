#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define MALLOC_OK 1
#define MALLOC_NO 0
#define CREATE_OK 1
#define CREATE_NO 0

struct hnode
{
	int num;
	
	struct hnode *next;
};

typedef struct hnode Hnode;
typedef Hnode * Hlink;

int is_malloc(Hlink new_node)
{
    if (NULL == new_node)
	{
		return MALLOC_NO;
	}
	return MALLOC_OK;
}

int create_new_node(Hlink *new_node)
{
    *new_node = (Hlink)malloc(sizeof(Hnode));
	if (MALLOC_OK == is_malloc(*new_node))
	{
		return CREATE_OK;
	}
	return CREATE_NO;
}

void create_hlink(Hlink *head)
{
    create_new_node(head);
	(*head)->next = NULL;
}

void insert_node_head(Hlink head,Hlink new_node)
{
	new_node->next = head->next;
    head->next = new_node;
}

void insert_node_tail(Hlink head,Hlink new_node)
{
	Hlink p = NULL;
	p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = new_node;
	new_node->next = NULL;
}

void insert_node_mid(Hlink head,Hlink new_node,int num)
{
    Hlink q = NULL,p = NULL;
	q = head;
	p = head->next;
	while(p != NULL && p->num != num)
	{
		q = p;
		p = p->next;
	}
	q->next = new_node;
	new_node->next = p;
}

void insert_node_sort(Hlink head,Hlink new_node)
{
    Hlink q = NULL,p = NULL;
	q = head;
	p = head->next;
	while(p != NULL && p->num < new_node->num)
	{
		q = p;
		p = p->next;
	}
	q->next = new_node;
	new_node->next = p;
}

#if 1
void reverse_Hlink(Hlink head)
{
	Hlink p1 = NULL,p2 = NULL,p3 = NULL;
	p1 = head->next;
	if (NULL == head->next)
	{
	    return ;
	}
	p2 = p1->next;
	if (NULL == head->next->next)
	{
	    p2->next = p1;
		head->next = NULL;
		head->next = p2;
	}
	p3 = p2->next;
	while (p3 != NULL)
	{
	    p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	p2->next = p1;
	head->next->next = NULL;
	head->next = p2;
}
#endif

Hlink seek_node(Hlink head,Hlink new_node,int num)
{
	Hlink p = NULL;
	p = head;
	while(NULL != p && p->num != num)
	{
		p = p->next;
	}
	if (NULL == p)
	{
		return NULL;
	}
	else
	{
		return p;
	}
}

void delete_node(Hlink head,int num)
{
	Hlink p = NULL,q = NULL;
	p = q = head;
	while(p != NULL && p->num != num)
	{
		q = p;
		p = p->next;
	}
	if (NULL == p)
	{
		printf("sorry no find this delete_node!\n");
	}
	else
	{
		q->next = p->next;
		free(p);
	}
}

void display_Hlink(Hlink head)
{
    Hlink p = NULL;
	if (NULL == head)
	{
		printf("no this Hlinlk!\n");
	}
	else if(NULL == head->next)
	{
	    printf("Hlink is empty!\n");
	}
	else
	{
		p = head->next;
	    while(p != NULL)
		{
		    printf("%d\n",p->num);
			p = p->next;
		}
	}
}

void empty_Hlink(Hlink head)
{
	Hlink p = NULL;
	p = head->next;
	while(p != NULL)
	{
	    head->next = p->next;
		free(p);
		p = head->next;
	}
}

void release_Hlink(Hlink *head)
{
	empty_Hlink(*head);
	free(*head);
	*head = NULL;
}

int main()
{
    Hlink head = NULL;
	Hlink new_node = NULL;
	int i,num;
	srand((unsigned)time(NULL));
	create_hlink(&head);
	for(i = 0;i < 10;i++)
	{
		if(CREATE_OK == create_new_node(&new_node))
		{
	//		new_node->num = i + 1;
	    	new_node->num = rand()%100;
		//	insert_node_head(head,new_node);
		//	insert_node_tail(head,new_node);
			insert_node_sort(head,new_node);
		}
	}
	printf("insert:Hlink is:\n");
	display_Hlink(head);
#if 1   //中间插入；
	if(CREATE_OK == create_new_node(&new_node))
	{
		printf("please input new_node num\n");
		scanf("%d",&new_node->num);
		printf("please input num\n");
		scanf("%d",&num);
	    insert_node_mid(head,new_node,num);
	}
	printf("insert_node_mid:Hlink is:\n");
	display_Hlink(head);
#endif
#if 1	
	printf("please input find node!\n");
	scanf("%d",&num);
	int node_num = seek_node(head,new_node,num)->num;//查找节点！
	printf("seek_node:Hlink is:\n");
	display_Hlink(head);
	printf("find node is %d\n",node_num);
#endif
	reverse_Hlink(head);
	printf("reserve:Hlink is :\n");
	display_Hlink(head);
	printf("please input delete node!\n");
	scanf("%d",&num);
	delete_node(head,num);
	printf("delete : Hlink is :\n");
	display_Hlink(head);
	empty_Hlink(head);
	printf("empty:Hlink is:\n");
	display_Hlink(head);
	release_Hlink(&head);
	printf("release:Hlink is :\n");
	display_Hlink(head);
	return 0;
}
