#include "address.h"

int is_malloc_ok(Link new_number_node)
{
    if (NULL == new_number_node)
	{
	    return MALLOC_NO;
	}
	return MALLOC_OK;
}

int create_address_number(Link * new_number_node)
{
	*new_number_node = (Link)malloc(sizeof(Link_Infor));
	if (MALLOC_OK == is_malloc_ok(*new_number_node))
	{
	    return MALLOC_OK;
	}
	return MALLOC_NO;

}

int create_address(Link * address_list)
{
	create_address_number(address_list);
    (*address_list)->next = NULL;
}

void inser_information(Link address_list,Link new_number_node)
{
    Link tail = NULL;
	tail = address_list;
	while(NULL != tail->next)
	{
	    tail = tail->next;
	};
	tail->next = new_number_node;
	new_number_node->next = NULL;
}

Link seek_address_number(Link address_list,int find)
{
    Link p = NULL;
	p = address_list->next;
	while(NULL != p && p->num != find)
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

void rev_number(Link address_list, Link rev_number_node,int rev_num)
{
    Link p = NULL,q = NULL;
	q = address_list;
	p = address_list->next;
	while (p != NULL && p->num != rev_num)
	{
		q = p;
	    p = p->next;
	}
	rev_number_node = p;
	q->next = rev_number_node;
	rev_number_node->next = p->next;
	free(p);
}

int delete_number(Link address_list,int del_num)
{
    Link p = NULL,q = NULL;
	q = address_list;
	p = address_list->next;
	while (NULL != p && p->num != del_num)
	{
		q = p;
	    p = p->next;
	}
	if (NULL == p)
	{
	    return DELETE_NO;
	}
	else 
	{
	    q->next = p->next;
		free(p);
		return DELETE_OK;
	}
}

void all_number(Link address_list)
{
    Link p = NULL;
	p = address_list->next;
	while (NULL != p)
    {
	    printf("序号：%2d\n",p->num);
		printf("名字：%2s\n",p->name);
		printf("性别：%2s\n",p->sex);
		printf("年龄：%2d\n",p->age);
		printf("电话号码：%2s\n",p->number);
		printf("地址：%2s\n",p->addr);
		p = p->next;
	}
}

int quit_address(Link * address_list)
{
    Link q = NULL,p = NULL;
	p = (*address_list)->next;
	if (NULL == *address_list)
	{
	    return QUIT_NO;
	}
	else
	{
		while (p != NULL)
		{
	    	(*address_list)->next = p->next;
        	free(p);
			p = (*address_list)->next;
			p = p->next;
		}
		free(*address_list);
		*address_list = NULL;
		return QUIT_OK;
	}
}







