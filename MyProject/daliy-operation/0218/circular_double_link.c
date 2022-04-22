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
    struct node *prior;
};

typedef struct node Node;
typedef Node * Cdlink;

int is_malloc_ok(Cdlink new_node)  //分配内存是否成功
{
    if(NULL == new_node)
    {
	return MALLOC_NO;
    }
    return MALLOC_OK;
}


int create_new_node(Cdlink *new_node)   //创建一个节点
{
    *new_node = (Cdlink)malloc(sizeof(Node));

    if(CREATE_OK == is_malloc_ok(*new_node))
    {
	return CREATE_OK;
    }
    return CREATE_NO;
}

int create_circular_double_link(Cdlink *head)   //创建循环双链表
{
    if(CREATE_OK == create_new_node(head))
    {
	(*head)->next = *head;
	(*head)->prior = *head;

	return CREATE_OK;
    }
    return CREATE_NO;
}

void insert_node_tail(Cdlink head, Cdlink new_node)   //尾插法
{
    Cdlink p = NULL;
    p = head->prior;

    p->next = new_node;
    new_node->prior = p;
    new_node->next = head;
    head->prior = new_node;

}

void insert_node_head(Cdlink head, Cdlink new_node)   //头插法
{
    new_node->next = head->next;
    head->next->prior = new_node;
    head->next = new_node;
    new_node->prior = head; 
}

void insert_node_mid_front(Cdlink head, Cdlink new_node, int num)  //中间插入，前
{
    Cdlink q = NULL, p = NULL;
    q = head;
    p = head->next;

    while(p != head && p->num != num )
    {
	q = p;
	p = p->next;
    }
    new_node->next = q->next;
    q->next->prior = new_node;
    q->next = new_node;
    new_node->prior = q;
}

void insert_node_mid_rear(Cdlink head, Cdlink new_node, int num)   //中间插入，后
{
    Cdlink p = NULL;
    p = head;

    while(p->next != head && p->num != num)
    {
	p = p->next;
    }
    new_node->next = p->next;
    p->next->prior = new_node;
    p->next = new_node;
    new_node->prior = p;
    
}

void insert_sort(Cdlink head, Cdlink new_node)   //插入并排序
{
    
    Cdlink q = NULL, p = NULL;
    q = head;
    p = head->next;

    while(p != head && p->num < new_node->num)
    {
	q = p;
	p = p->next;
    }
    new_node->next = q->next;
    q->next->prior = new_node;
    q->next = new_node;
    new_node->prior = q;
}

void delete_node(Cdlink head, int num)  //删除一个节点
{
    Cdlink p = NULL, q = NULL;
    q = head;
    p = head->next;

    while(p != head && p->num != num)
    {
	q = p;
	p = p->next;
    }

    if(p == head)
    {
	printf("not find delete node!\n");
	return ;
    }
    else
    {
	q->next = p->next;
	p->next->prior = q;
	free(p);
    }
}

Cdlink seek_node(Cdlink head, int num)  //查找一个节点
{
    Cdlink p = NULL;
    p = head->next;

    while(p != head && p->num != num)
    {
	p = p->next;
    } 

    if(p == head)
    {
	printf("not find node!\n");
	return NULL;
    }
    else
    {
	return p;
    }
}

int count_length(Cdlink head)   //计算表长
{
    int count = 0;
    Cdlink p = NULL;
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

void reverse_link(Cdlink head)  //逆序链表(是错误的，不用逆序)
{
    Cdlink p1 = NULL, p2 = NULL, p3 = NULL;
    p1 = head->next;

    if(p1 == head)
    {
	printf("the link is NULL!\n");
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
	 p2->prior = p2->next;
	 p2->next = p1;
	 p1 = p2;
	 p2 = p3;
	 p3 = p3->next;
    }

    p2->prior = p2->next;
    p2->next = p1;

    head->prior = head->next;
    head->next = p2;

}

void reverse_display(Cdlink head)  //反向遍历
{
    Cdlink p = NULL;

    if(head == NULL)
    {
	printf("the link is not exit!\n");
	return ;
    }
    else if(head->next == head)
    {
	printf("the link is NULL!\n");
	return ;
    }
    else
    {
        p = head->prior;
        
	while(p != head)
	{
            printf("%d\n", p->num);
	    p = p->prior;
	}
    }
}

void make_empty(Cdlink head)   //清空链表
{
    Cdlink p = NULL;
    p = head->next;

    while(p != head)
    {
	head->next = p->next;
	p->next->prior = head;
	free(p);
	p = head->next;
    }

}
    
void release_link(Cdlink *head) //释放链表
{
    make_empty(*head);

    free(*head);

    *head = NULL;
}
    
void display_link(Cdlink head)  //遍历链表
{
    Cdlink p = NULL;

    if(head == NULL)
    {
	printf("the link not exit!\n");
	return ;
    }
    else if(head->next == head)
    {
	printf("the link is NULL!\n");
	return ;
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
    Cdlink head = NULL;
    Cdlink new_node = NULL;
    int i;
    int num;
    srand((unsigned)time(NULL));

    if(CREATE_NO == create_circular_double_link(&head))   //创建循环双链表
    {
	return 0;
    }
    
    for(i = 0; i < 10; i++)
    {
        if(CREATE_OK == create_new_node(&new_node))   //创建一个节点
        {
	    //new_node->num = i + 1;
	    new_node->num = rand()%100;
            //insert_node_tail(head, new_node);   //尾插法
            //insert_node_head(head, new_node);   //头插法
            insert_sort(head, new_node);   //插入并排序
        }
    }	
    display_link(head);  //遍历链表

#if 0   //从中间插入数据
    if(CREATE_OK == create_new_node(&new_node))
    {
	printf("please insert of number:\n");
	scanf("%d", &num);

	printf("insert node of information:");
	scanf("%d", &new_node->num);

        //insert_node_mid_front(head, new_node, num);  //中间插入，前
        insert_node_mid_rear(head, new_node, num);   //中间插入，后
        display_link(head);  //遍历链表
    }
#endif

#if 0    //删除一个节点
    printf("please input number of delete:");
    scanf("%d", &num);
    delete_node(head, num);  //删除一个节点
    display_link(head);  //遍历链表
#endif

#if  0   //查找一个节点
    Cdlink p = NULL;
    printf("please input number of seek:");
    scanf("%d", &num);
    p = seek_node(head, num);  //查找一个节点
    if(p != NULL)
    {
	printf("%d\n", p->num);
    }
#endif

#if 0     //计算表长
    int count;
    count = count_length(head);   //计算表长
    printf("the link length is:%d\n", count);
#endif

#if 0   //没有逆序，不要这个功能
    reverse_link(head);  //逆序链表
    display_link(head);  //遍历链表
#endif

#if 0    //反向遍历，逆序输出
    printf("reverse display link Is:\n");
    reverse_display(head);  //反向遍历
#endif
    make_empty(head);   //清空链表
    display_link(head);  //遍历链表

    release_link(&head); //释放链表
    display_link(head);  //遍历链表


    return 0;
}
