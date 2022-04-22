#include "address.h"

void menu()
{
    printf("*****************************************************\n");
    printf("*****************************************************\n");
	printf("************        欢迎来到通讯录       ************\n");
    printf("*****************************************************\n");
    printf("*****************************************************\n");
	printf("************        1、增加联系人        ************\n");
	printf("************        2、查看联系人        ************\n");
	printf("************        3、删除联系人        ************\n");
	printf("************        4、修改联系人        ************\n");
	printf("************        5、显示所有联系人    ************\n");
	printf("************        6、保存通讯录        ************\n");
	printf("************        7、退出通讯录        ************\n");
    printf("*****************************************************\n");
    printf("*****************************************************\n");

}

void save_address(Link address_list)
{
    int to_file;
	int n_write;
	Link ptr = NULL;
	Link q = NULL;
	ptr = address_list->next;

	to_file = open("./address.text",O_CREAT | O_WRONLY,S_IRUSR | S_IWUSR | S_IRGRP);
	if (n_write != -1)
	{
	    printf("save address sucess!\n");
	}
	if (ptr == NULL)
	{
		printf("通讯录是空的无法写入");
	}
	while (ptr != NULL)
	{
		n_write = write(to_file,ptr,sizeof(Link_Infor));
		ptr = ptr->next;
	}
	printf("保存成功！\n");
	close(to_file);
}

void open_address(Link address_list)
{
    int n_read;
	int from_file;
	Link p = NULL;
	from_file = open("./address.text",O_CREAT | O_RDONLY,S_IRUSR | S_IWUSR | S_IRGRP);
	if (from_file == -1)
	{
	    perror("error!\n");
		exit(-1);
	}
	while (1)
	{
	    create_address_number(&p);
		n_read = read(from_file,p,sizeof(Link_Infor));
		if (0 == n_read)
		{
		    break;
		}
		p->next = address_list->next;
		address_list->next = p;
	}
    if (n_read == EOF)
	{
	    printf("open address success!\n");
	}
	else
	{
	    printf("open address fail!\n");
	}
	close(from_file);
}

void select_oper(Link address_list,int input)
{
	Link new_number_node = NULL;
	Link rev_number_node = NULL;
	int find,del_num,rev_num,rev_sel_num,ret_quit,num = 0;
	int quit = 0;
    switch(input)
	{
		case 1:
	        printf("请输入增加的联系人信息!\n");
		    if(MALLOC_OK == create_address_number(&new_number_node))//创建新成员节点；
		    {
		        printf("请输入序号:\n");
			    scanf("%d",&new_number_node->num);
			    printf("请输入联系人姓名\n");
				scanf("%s",new_number_node->name);
				printf("请输入性别:\n");
            	scanf("%s",new_number_node->sex);
				printf("请输入年龄:\n");
				scanf("%d",&new_number_node->age);
				printf("请输入电话号码:\n");
            	scanf("%s",new_number_node->number);
				printf("请输入地址:\n");
				scanf("%s",new_number_node->addr);
				inser_information(address_list,new_number_node);//将成员信息插入通讯录；		
				
			}
			else
			{
		    	printf("增加失败！！！\n");
			}
			break;
		case 2:
			printf("请输入了要查找联系人的序号:\n");
			scanf("%d",&find);
			Link ret_find = seek_address_number(address_list,find);
			if (NULL == ret_find)
			{
			    printf("对不起，要找到联系人不存在！！！\n");
			}
			else
			{
			    printf("已查找到该联系人！\n");
				printf("序号：%2d\n",ret_find->num);
				printf("姓名：%2s\n",ret_find->name);
				printf("性别：%2s\n",ret_find->sex);
				printf("年龄：%2d\n",ret_find->age);
				printf("电话号码：%2s\n",ret_find->number);
				printf("地址：%2s\n",ret_find->addr);
			}
			break;
		case 3:
			printf("请输入要删除联系人的序号：\n");
            scanf("%d",&del_num);
			int ret_del = delete_number(address_list,del_num);
			if (DELETE_NO == ret_del)
			{
			    printf("删除的联系人不存在！！！\n");
			}
			else
			{
			    printf("删除成功！！！\n");
			}
			break;
		case 4:
			printf("请输入需要修改的联系人的序号：\n");
			scanf("%d",&rev_num);
			create_address_number(&rev_number_node);
			printf("请选择想要的修改信息\n");
			while (rev_sel_num != 2)
			{
			    printf("1、姓名 2、性别3、年龄 4、电话号码 5、地址\n");
			    scanf("%d",&rev_sel_num);
				if (1 == rev_sel_num)
				{
				    printf("请输入想要修改的姓名：\n");
					scanf("%s",rev_number_node->name);
				}
				else if (2 == rev_sel_num)
				{
				    printf("请输入想要修改的性别：\n");
					scanf("%s",rev_number_node->sex);
				}
				else if (3 == rev_sel_num)
				{
				    printf("请输入想要修改的年龄：\n");
					scanf("%d",&rev_number_node->age);
				}
				else if (4 == rev_sel_num)
				{
				    printf("请输入想要修改的电话号码：\n");
					scanf("%s",rev_number_node->number);
				}
				else if (5 == rev_sel_num)
				{
				    printf("请输入想要修改的地址：\n");
					scanf("%s",rev_number_node->addr);
				}
				else
				{
				    printf("输入有误！请重新输入！\n");
					scanf("%d",&rev_sel_num);
				}
				rev_number(address_list,rev_number_node,rev_num);
				printf("是否还想修改? 1、是 2、否\n");
				scanf("%d",&num);
				if (2 == num)
				{
				    rev_sel_num = 2;
					break;
				}
			}
			break;
		case 5:
			printf("所有联系人信息如下：\n");
			all_number(address_list);
			break;
		case 6:
			save_address(address_list);
			break;
		case 7:
			while(quit != 1 && quit != 2)
			{
				printf("确定退出吗？\n");
				printf("!、确定 2、取消 \n");
				scanf("%d",&quit);
				if (2 == quit)
				{
			    	printf("取消退出......\n");
					break;
				}
				else if (1 == quit)
				{
					ret_quit = quit_address(&address_list);
					if(QUIT_NO == ret_quit)
					{
					    printf("退出失败！！！\n");
					}
					printf("正在退出...\n");
					exit(0);
					break;
				}
				else
				{
			    	printf("输入有误，请重新输入！！！\n");
					printf("确定退出吗？\n");
					printf("!、确定 2、取消 \n");
					scanf("%d",&quit);
				}
			}
			break;
	}
}

void test()
{
    int input = 0;
    Link address_list = NULL;
	create_address(&address_list);//创建空的通讯录；
	open_address(address_list);
	do
	{
	    menu();
		printf("请进行选择:\n");
		scanf("%d",&input);
		select_oper(address_list,input);
	}
	while(input);
}

int main(int argc,char **argv)
{
    test();
    return 0;
}
