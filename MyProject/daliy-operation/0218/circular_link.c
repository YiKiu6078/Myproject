#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define CREATE_OK 1
#define CREATE_NO 0
#define MALLOC_OK 1
#define MALLOC_NO 0

struct node
{
   int num;

   struct node *next;
};

typedef struct node Node;
typedef Node * Clink;

int is_malloc_ok(Clink new_node)  //分配存储空间是否成功
{
    if(NULL == new_node)
    {
	return MALLOC_NO;
    }
    return MALLOC_OK;
}
    

int create_new_node(Clink *new_node)    //创建链表节点
{
    *new_node = (Clink)malloc(sizeof(Node));

    if(CREATE_OK == is_malloc_ok(*new_node))
    {
	return CREATE_OK;
    }
    return CREATE_NO;
}

int create_circular_link(Clink *head)  //创建循环链表
{
    if(CREATE_OK == create_new_node(head))
    {
        (*head)->next = *head;
	return CREATE_OK;
    }
    else
    {
	return CREATE_NO;
    }
}


void insert_node_tail(Clink head, Clink new_node)  //尾插法
{
    Clink p = NULL;
    p = head;

    while(p->next != head)
    {
	p = p->next;
    }
    p->next = new_node;
    new_node->next = head;
}

void insert_node_head(Clink head, Clink new_node)  //头插法
{
    new_node->next = head->next;
    head->next = new_node;
}

void insert_node_mid_rear(Clink head, Clink new_node, int num) //中间插入，在节点后
{
    Clink p = NULL;
    p = head;

    while(p->next != head && p->num != num)
    {
	p = p->next;
    }
    new_node->next = p->next;
    p->next = new_node;
}

void  insert_node_mid_front(Clink head, Clink new_node, int num)  //中间插入，在节点前
{
    Clink p = NULL, q = NULL;
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

void insert_sort(Clink head, Clink new_node)  //插入时排序
{
    Clink p = NULL, q = NULL;
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
    

void delete_node(Clink head, int num)   //删除节点
{
    Clink p = NULL, q = NULL;
    q = head;
    p = head->next;

    while(p != head && p->num != num)
    {
	q = p;
	p = p->next;
    }
    if(p == head)
    {
	printf("no node\n");
	return ;
    }
    else
    {
	q->next = p->next;
	free(p);
    }
}

Clink seek_node(Clink head, int num)  //查找节点
{
    Clink p = NULL;
    p = head->next;

    while(p != head && p->num != num)
    {
	p = p->next;
    }
    if(p == head)
    {
	return NULL;
    }
    else
    {
	return p;
    }

}

int count_link_long(Clink head)  //计算链表长度
{
    int count = 0;
    Clink p = NULL;
    p = head->next;
    
    if(p == head)
    {
	return 0;
    }

    while(p != head)
    { 
	count++;
        p = p->next;
    }
    return count;

}
void reverse_link(Clink head)  //逆序链表
{
    Clink p1 = NULL, p2 = NULL, p3 = NULL;
    p1 = head->next;

    if(p1 == head)
    {
	printf("the link is NULL\n");
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
	p1 =p2;
	p2 = p3;
        p3 = p3->next;
    }
    
    p2->next = p1;

    head->next->next = head;

    head->next = p2;


}

void make_empty(Clink head)  //清空链表
{
    Clink p = NULL;
    p = head->next;
    
    while (p != head)
    {
	head->next = p->next;
	free(p);
	p = head->next;
    }

}

void release_link(Clink *head)  //释放链表
{
    make_empty(*head);

    free(*head);

    *head = NULL;
}

void display_link(Clink head)  //遍历链表
{
    Clink p = NULL;

    if(head == NULL)
    {
	printf("the link reverse!\n");
	return ;
    }
    else if (head == head->next )
    {
	printf("the link is NULL!\n");
    }
    else
    {
	
        p = head->next;

        while(p != head)
        {
	    printf("%d\n", p->num);
	    p = p->next;
        }    
    }
	
}

int main()
{
    Clink head = NULL;
    Clink new_node = NULL;
    int num;
    int i;
    srand((unsigned)time(NULL));

    if(CREATE_NO == create_circular_link(&head))  //创建循环链表
    {
	return 0;
    }

    for(i = 0; i < 10; i++)
    {
        if(CREATE_OK == create_new_node(&new_node))    //创建链表节点
        {
	    //new_node->num = i + 1;	
	    new_node->num = rand()%100;
            //insert_node_tail(head, new_node);  //尾插法
            //insert_node_head(head, new_node);  //头插法
            insert_sort(head, new_node);  //插入时排序
        }
    }
    display_link(head);
    
#if 1
    if(CREATE_OK == create_new_node(&new_node))    //创建链表节点
    {
	printf("please input of number:\n");
	scanf("%d", &num);

	printf("insert of number is:");
	scanf("%d", &new_node->num);

        insert_node_mid_rear(head, new_node, num); //中间插入，在节点后
        //insert_node_mid_front(head, new_node, num);  //中间插入，在节点前
        display_link(head);  //遍历链表
    }
#endif

#if 0
    printf("delete node is:");
    scanf("%d", &num);
    delete_node(head, num);   //删除节点
    display_link(head);  //遍历链表
#endif

#if 0 
    Clink p = NULL;
    printf("seek node is:");
    scanf("%d", &num);    
    p = seek_node(head, num);  //查找节点
    if(p == NULL)
    {
	printf("seek is not!\n");
    }
    else
    {
	printf("%d\n", p->num);
    }
#endif

#if 0
    int count;
    count = count_link_long(head);  //计算链表长度
    printf("the link long:%d\n", count);
#endif

#if 0
    printf("the reverse is:\n");
    reverse_link(head);  //逆序链表
    display_link(head);  //遍历链表
#endif

    make_empty(head);  //清空链表表
    display_link(head);  //遍历链表

    release_link(&head);  //释放链表
    display_link(head);  //遍历链表

    return 0;
}

