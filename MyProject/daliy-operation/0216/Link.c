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
	char name[20];
	char sex;
	int age;
	int add[100];

	struct node *next;
};

typedef struct node Node;
typedef Node * Link;

void creat_link(Link *head)
{
    *head = NULL;
}

int is_malloc(Link new_node)
{
	if (NULL == new_node)
	{
		printf("malloc is empty!\n");
		return MALLOC_NO;
	}
	else
	{
	    return MALLOC_OK;
	}
}

int creat_new_node(Link *new_node)
{
    *new_node = (Link)malloc(sizeof(Node));
	if (MALLOC_OK ==  is_malloc(*new_node))
	{
	    return CREATE_OK;
	}\
	else
	{
		return CREATE_NO;
	}
}

void insert_node_head(Link *head,Link new_node)
{
	new_node->next = *head;
	*head = new_node;
}

#if 1
void insert_node_tail(Link *head,Link new_node)
{
	Link p = NULL;
	p = *head;
	if (NULL == p)
	{
		*head = new_node;
		new_node->next = NULL;
	}
	else
	{
		while (p->next != NULL)
		{
	    	p = p->next;
		}
		p->next = new_node;
		new_node->next = NULL;
	}
}
#endif

void insert_node_mid(Link *head,Link new_node,int loc)
{
	Link p = NULL;
	Link q = NULL;
	p = q = *head;
	while(p != NULL && p->num != loc)
	{
	    q = p;
		p = p->next;
	}//保证p与q相邻；
	if (p == *head)
	{
	    new_node->next = *head;
		*head = new_node;
	}
	else
	{
	    q->next = new_node;
		new_node->next = p;
	}
}

void insert_node_sort(Link *head,Link new_node)
{
    Link p = NULL,q = NULL;
	q = p = *head;
	while (p != NULL && p->num < new_node->num )
	{
	    q = p;
		p = p->next;
	}
	if (p == *head)
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
	    q->next = new_node;
		new_node->next = p;
	}

}

void display_link(Link head)
{
    Link p = NULL;
	p = head;
	if (NULL == p)
	{
	    printf("Link is empty!\n");
	}
	while (p != NULL)
	{
		printf("%d\n",p->num);
		p = p->next;
	}
}

void seek_node(Link head,int num)
{
	Link p = NULL;
	p = head;
	if (NULL == head)
	{
	    printf("Link is empty!\n");
	}
	else
	{
	    while(p != NULL && p->num != num)
		{
			p = p->next;
		}
		if(NULL == p)
		{	
		    printf("sorry no find!\n");
		}
		else
		{
			printf("find this node is %d \n",p->num);
		}
	}
}
#if 1
void delete_node(Link *head,int num)
{
    Link q = NULL, p = NULL;
	q = p = *head;
	while(p != NULL && p->num != num)
	{
		q = p;
		p = p->next;
	}
	if (NULL == p)
	{
	    printf("num is error!\n");
	}
	else if(p == *head)
	{
		*head = (*head)->next;
		free(p);
	}
	else
	{
		q->next = p->next;
		free(p);
	}

}
#endif

void reverse_link(Link *head)
{
    Link p1 = NULL;
    Link p2 = NULL;
    Link p3 = NULL;
	if (NULL == *head)
	{
		printf("reverse:link is empty!\n");
	}
	p1 = *head;
	if (NULL == (*head)->next)
	{
		return ;
	}
	p2 = p1->next;
	p3 = p2->next;
	while(p3 != NULL)
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	p2->next = p1;
	(*head)->next = NULL;
	*head = p2;
}

void release_link(Link *head)
{
	Link p = NULL;
	p = *head;
	if (NULL == *head)
	{
		printf("Link is empty!\n");
	}
	while (p != NULL)
	{
		*head = (*head)->next;
		free(p);
		p = *head;
	}
}

int main()
{
    Link head = NULL;
	Link new_node = NULL;
	int i,loc,num;
	srand((unsigned)time(NULL));

	creat_link(&head);
	for (i = 0;i < 10;i++)
	{
		if (CREATE_OK == creat_new_node(&new_node))
		{
	//	    new_node->num = i + 1;
			new_node->num = rand()%100;
		//	insert_node_head(&head,new_node);
		//	insert_node_tail(&head,new_node);
			insert_node_sort(&head,new_node);
		}
	}
#if 0  //中间插入；
	printf("please input location:\n");
	scanf("%d",&loc);
	if (CREATE_OK == creat_new_node(&new_node))
	{
		printf("please input num:\n");
		scanf("%d",&new_node->num);
		insert_node_mid(&head,new_node,loc);
	}
#endif
	display_link(head);
	printf("please input find node!\n");
	scanf("%d",&num);
	seek_node(head,num);
	printf("please input delete node!\n");
	scanf("%d",&num);
	delete_node(&head,num);
	display_link(head);
	printf("reverse_link is :\n");
	reverse_link(&head);
	display_link(head);
	release_link(&head);
	display_link(head);

	return 0;
}
