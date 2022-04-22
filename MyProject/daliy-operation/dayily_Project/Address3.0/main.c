#include "address.h"

void menu1()
{
    printf("*****************************************************\n");
    printf("*****************************************************\n");
	printf("************        欢迎来到通讯录       ************\n");
    printf("*****************************************************\n");
    printf("*****************************************************\n");
	printf("************        1、增加联系人        ************\n");
	printf("************        2、删除联系人        ************\n");
	printf("************        3、修改联系人        ************\n");
	printf("************        4、查看联系人        ************\n");
	printf("************        5、查看所有联系人    ************\n");
	printf("************        0、退出通讯录        ************\n");
    printf("*****************************************************\n");
    printf("*****************************************************\n");

}

void menu2()
{
    printf("*****************************************************\n");
    printf("*****************************************************\n");
	printf("************       正在退出通讯录···     ************\n");
    printf("*****************************************************\n");
    printf("*****************************************************\n");
	printf("************        欢迎再次使用！       ************\n");
    printf("*****************************************************\n");
}

void address(sqlite3 * adr)
{
	int input;
	int ret;
	
    do
	{
	    menu1();//开始菜单
		printf("please select your operation!\n");
		scanf("%d",&input);
		switch(input)
		{
		    case 1:
				ret = insert_scord(adr);//插入联系人记录
				if (ret == SQLITE_OK)
				{
					printf("insert scord success!\n");
				}
				break;
			case 2:
                ret = delete_scord(adr);//删除联系人记录
				if (SQLITE_OK == ret)
				{
				    printf("delete scord success!\n");
				}
				break;
			case 3:
				ret = update_scord(adr);//修改联系人记录
				if (SQLITE_OK == ret)
				{
				    printf("update scord success!\n");
				}
				break;
			case 4:
				ret = inquire_scord(adr);//根据ID查询联系人---不使用回调函数法
				break;
			case 5:
				ret = inquire_all_scord(adr);//查询所有联系人
				break;
			case 0:
				menu2();//退出菜单
				break;
			default :
				printf("select error!please select again!\n");
				break;
		}
	}
	while(input);
}

int main(int argc,char ** argv)
{
	int ret;
	sqlite3 * adr = NULL;
	ret = sqlite3_open("address.db",&adr);//打开数据库
	if (SQLITE_OK != ret)
	{
		printf("open address.db error!%s\n",sqlite3_errmsg(adr));
		exit(EXIT_FAILURE);
	}
	if (SQLITE_OK == create_address(adr))//判断通讯录这张表是否创建成功
	{
		address(adr);//创建成功进入函数进行操作
	}
	else
	{
		sqlite3_close(adr);
		exit(0);
	}
    sqlite3_close(adr);//关闭数库
	return 0;
}
