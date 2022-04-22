/*****链表处理调用函数*****/


#include "myhead.h"


//初始化
int online_init(Node *head)
{
    *head = (Node)malloc(sizeof(struct online));
    if (NULL == *head)
    {
        return F;
    }
    
    (*head)->next = NULL;
	return 0;
}

//上线
int online_insert(Node *head, int fd, char *id, char *name)
{
    Node p,s;
	
	s = (Node)malloc(sizeof(struct online));
    if (NULL == s)
    {
        return F;
    }    

	if((*head)->next == NULL) //说明此时为空链表，头结点指针域为空
	{
		strcpy(s->id , id);
		s->fd = fd;
		s->forbid = 0;
		(*head)->next = s;
		s->next = NULL;
	}
	else
	{
		p = (*head)->next;
		while(p->next != NULL)
		{
			p = p->next;
		}
		strcpy(s->id , id);
		s->fd = fd;
		s->forbid = 0;
		
		s->next = p->next;
		p->next = s;
	}
	
    printf("用户 %s 在客户端 %d 已经上线 \n",s->id,s->fd);
    return T;
}


//查找的是fd,查找不到，返回0
int locate(Node head, int fdd)
{
	printf("开始找\n");
	int i=0;
    Node p=head->next;//p是第一个节点
    while(p != NULL)//终止条件是p不是空接点，
    {
        i++;	
		if(p->fd == fdd)	//找到这样的数据元素
		{
			return i;
        }
		p=p->next;
    }
    return 0;
}
//下线
int delete(Node *head, int i)
{
	printf("开始删\n");
    int j = 1;
    Node temp,q;
	temp = (*head);
    while (temp->next != NULL && j < i)
    {
        temp = temp->next;
        ++j;
    }
    if((temp->next) == NULL || j > i)
    {
        return F;
    }
	q = temp->next;
	temp->next = q->next;
	free(q);
 
    return 0;
}

//xiaxian---------------
void delete_id(Node *head, int fd)
{
	printf("退出的客户端号%d\n",fd);
	int ret;
	int fdd;
	fdd = fd;
	ret=locate(*head,fdd);
	printf("找到这个人在第%d个\n",ret);
	delete(head,ret);
	printf("退出成功\n");
}


//遍历打印
int online_display(Node head, int fd, char *id)
{
    Node temp;
	temp = head->next;
	
    while(temp != NULL)
    {	
			printf("进入while\n");
			
			printf("temp->id=%s\n",temp->id);
			printf("temp->fd=%d\n",temp->fd);
			printf("temp->forbid=%d\n",temp->forbid);
            temp = temp->next;
	}
	return 0;
}



//遍历查找登录信息插入链表的时候，然后判断进入的人online_check(head,fd,Msg.id,Msg);
int online_check(Node head,int fd, char *id,struct message *Msg)//有回馈
{
	
    Node temp = head->next;
    int flag1 = 1;
	int sendcnt = 0;
    while(temp != NULL)
    {
        if(strcmp(temp->id,Msg->id) == 0)
		//if(temp->next->id == Msg.id)
		{
		printf("赋值后temp->next->id=%s\n",temp->id);
			flag1 = 0;break;
		}
		else
		{
			printf("传过来的id=%s\n",id);
			printf("链表里的temp->next->id=%s\n",temp->id);
			temp = temp->next;
		}
    }
 
	if(flag1 == 1)
	{
		char succ[50] ="登录成功！用户--";
		strcat(succ,Msg->id);
		strcpy(Msg->buff,succ);
		//Msg.toid = fd;
		Msg->backid = 1;
		printf("Msg.backid=%d\n",Msg->backid);
		
		sendcnt = write(fd,Msg,sizeof(*Msg));
		

		
		if(sendcnt != -1)
		{
			printf(GREEN"%s\n登录成功！\n",Msg->id);
			printf(DEFAULT);
		}
					
	}
	else
	{
		printf(RED"该用户已在线链表！重复登录失败");
		printf(DEFAULT);
		Msg->backid = 0;
	}
					
					
	return flag1;
}


//遍历查找把链表里的id提取出来给fromid  online_send1(head,fd,&Msg)
int online_send1(Node head, int fd, struct message *Msg)
{
	//根据fd找发送方id
	Node temp = head;
    while(temp != NULL)
    {
		printf("进入第一个send找到是哪个用户发的\n");
	    if (temp->fd == fd)
        {
			
			printf("temp->id=%s\n",temp->id);
			printf("temp->fd=%d\n",temp->fd);
			printf("第一个send成功了\n");
			Msg->fromid = atoi(temp->id);
			break;
		}
        else
        {			
			printf("send1链表里的temp->id=%s\n",temp->id);
            temp = temp->next;
        }
		
	}	
	return 0;

}


//遍历查找根据toid找到fd，发消息过去 online_send2(head,fd,&Msg)
int online_send2(Node head, int fd, struct message *Msg)
{
	//根据toid找接收方fd
    Node temp = head;
    while(temp != NULL)
    {
		printf("进入第二个send找到是要发给用户的客户端号\n");
	    if (atoi(temp->id) == Msg->toid)
        {
			
			printf("temp->id=%s\n",temp->id);
			printf("temp->fd=%d\n",temp->fd);
			printf("第二个send成功了\n");
			Msg->toid = temp->fd;
			break;
		}
        else
        {
			//printf("发送方id=%s\n",Msg.id);
			printf("send2链表里的temp->id=%s\n",temp->id);
            temp = temp->next;
        }
		//temp = temp->next;
	}	
	return 0;
			
}


//遍历查找把链表里所有的fd提取出来给toid  online_sendall(head,fd,&Msg)
int online_sendall(Node head, int fd, struct message *Msg)
{
	
	int sendcnt = 0;
	Node temp = head->next;
    while(temp != NULL)
    {
		Msg->toid = temp->fd;
		while(Msg->toid != 0)
		{
			sendcnt = write(Msg->toid,Msg,sizeof(*Msg));
			if(sendcnt != -1)
			{
				printf("服务器向客户端%d 发送了数据：%s\n",Msg->toid,Msg->buff);
			}
			break;
		}
		temp = temp->next;
	
	}	
	return 0;

}


//遍历查找把链表里的forbid提取出来给adimn  online_send3(head,fd,&Msg)
int online_send3(Node head, int fd, struct message *Msg)
{

	Node temp = head;
    while(temp != NULL)
    {
		printf("进入第三个send找禁言标志位\n");
	    if (temp->fd == fd)
        {
			printf("temp->fd=%d\n",temp->fd);
			printf("temp->forbid=%d\n",temp->forbid);
			printf("第三个send成功了\n");
			Msg->admin = temp->forbid;
			break;
		}
        else
        {			
			printf("send1链表里的temp->id=%s\n",temp->id);
            temp = temp->next;
        }
		
	}	
	return 0;

}

//遍历查找被禁言的人的标志位  online_forbid(head,&Msg)
int online_forbid(Node head,struct message *Msg)
{
	
	Node temp = head;
    while(temp != NULL)
    {
		printf("找到将要被禁言的人的id\n");
	    
		
		if (strcmp(temp->id,Msg->user) == 0)
        {
			
			printf("temp->id=%s\n",temp->id);
			printf("temp->fd=%d\n",temp->fd);
			printf("将要被禁言的人找成功了\n");
			temp->forbid = 1;//禁言
			break;
		}
        else
        {			
			printf("刚刚找的链表里的temp->id=%s\n",temp->id);
            temp = temp->next;
        }
		
	}	
	return 0;

}



//遍历查找需要解除禁言的人的标志位  online_allow(head,&Msg)
int online_allow(Node head,struct message *Msg)
{
	
	Node temp = head;
    while(temp != NULL)
    {
		printf("找到需要解除禁言的人的id\n");
	    
		
		if (strcmp(temp->id,Msg->user) == 0)
        {
			
			printf("temp->id=%s\n",temp->id);
			printf("temp->fd=%d\n",temp->fd);
			printf("需要解除禁言的人找成功了\n");
			temp->forbid = 0;//解除禁言
			break;
		}
        else
        {			
			printf("刚刚找的链表里的temp->id=%s\n",temp->id);
            temp = temp->next;
        }
		
	}	
	return 0;

}

//遍历查找被踢的人的ID信息对应的fd并从链表中删除  online_kick(head,&Msg)
int online_kick(Node head,struct message *Msg)
{
	
	Node temp = head;
    while(temp != NULL)
    {
		printf("找到将要被踢的人的id\n");
	    
		
		if (strcmp(temp->id,Msg->user) == 0)
        {
			int ffd = 0;
			printf("temp->id=%s\n",temp->id);
			printf("temp->fd=%d\n",temp->fd);
			printf("将要被踢的人找成功了\n");
			ffd = temp->fd; //准备踢人从链表中移除
			
			delete_id(&head,ffd);
			
			Msg->kick = 1;
			
			break;
		}
        else
        {			
			printf("刚刚找的链表里的temp->id=%s\n",temp->id);
            temp = temp->next;
        }
		
	}	
	return 0;

}

//遍历查找根据user找到fd，发消息过去 online_kicked(head,&Msg)
int online_kicked(Node head,struct message *Msg)
{
    Node temp = head;
    while(temp != NULL)
    {
		printf("找到刚刚被踢用户的客户端号\n");
	    if (strcmp(temp->id,Msg->user) == 0)
        {
			
			printf("temp->id=%s\n",temp->id);
			printf("temp->fd=%d\n",temp->fd);
			printf("刚刚被踢用户的客户端号找到了\n");
			Msg->toid = temp->fd;
			break;
		}
        else
        {
			//printf("发送方id=%s\n",Msg.id);
			printf("kicked链表里的temp->id=%s\n",temp->id);
            temp = temp->next;
        }
		//temp = temp->next;
	}	
	return 0;
			
}







