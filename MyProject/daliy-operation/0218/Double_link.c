#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node
{
	int num;

	struct node *prior,*next;
};

typedef struct node Node;
typedef Node * DoubleLink;

void create_new_node(DoubleLink * new_node)
{
	*new_node = (DoubleLink)malloc(sizeof(Node));
}

void create_doublink(DoubleLink * head)
{
	create_new_node(head);
	(*head)->next = *head;
	(*head)->prior = *head;
}

void insert_node_head(DoubleLink head,DoubleLink new_node)
{
	new_node->next = head->next;//新节点的后继为头节点的后继
	head->next->prior = new_node;//第二个节点前驱指向新节点
	head->next = new_node;//头结点后继指向新节点
	new_node->prior = head;//新节点的前驱指向头结点
}

void insert_node_tail(DoubleLink head,DoubleLink new_node)
{
	DoubleLink p = NULL;
//	p = head->prior;//p为尾节点；
	
//	p->next = new_node;//尾节点指向新节点
	new_node->prior = head->prior;//新节点前驱为尾节点
	new_node->next = head;//新节点的后继为头节点
	head->prior->next = new_node;//头结点的前驱指向新节点
	head->prior = new_node;

}

void insert_node_mid(DoubleLink head,DoubleLink new_node,int num)
{
	DoubleLink p = NULL,q = NULL;
	q = head;
	p = head->next;
	while  (p != head && p->num != num)
	{
		q = p;
	    p = p->next;
	}
	if (head == p)
	{
	    printf("insert error!\n");
	}
	else
	{
		new_node->next = p;
		new_node->prior = q;
    	p->prior = new_node;
		q->next = new_node;
	}
}
void display_doublelink(DoubleLink head)
{
    DoubleLink p = NULL;
	if (NULL == head)
	{
		printf("no this DoubleLink!\n");
	}
	else if (head->prior == head)
	{
	    printf("DoubleLink is empty!\n");
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

void releae_dbllink(DoubleLink *head)
{
    DoubleLink p = NULL;
	p = (*head)->next;
	while(p != (*head))
	{
	    (*head)->next = p->next;
		free(p);
		p = p->next;
	}
	free(*head);
	*head = NULL;
}

int main(int argc ,char **argv)
{
	DoubleLink head = NULL;
	DoubleLink new_node = NULL;

	int i,num;

	create_doublink(&head);
	for(i = 0;i < 10;i++)
	{		
		create_new_node(&new_node);
		new_node->num = i + 1;
	//	insert_node_head(head,new_node);
		insert_node_tail(head,new_node);
	}
	display_doublelink(head);
	
	printf("please input node_num\n");
	scanf("%d",&num);
	create_new_node(&new_node);
	printf("please input num\n");
	scanf("%d",&new_node->num);
	insert_node_mid(head,new_node,num);
	display_doublelink(head);
    releae_dbllink(&head);
	display_doublelink(head);
	return 0;
}
