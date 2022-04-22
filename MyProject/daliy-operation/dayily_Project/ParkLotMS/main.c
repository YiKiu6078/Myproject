#include "park_lot.h"

void menu()
{
    printf("*************************************************\n");
    printf("*************************************************\n");
    printf("*****           WELCOME TO PARKING          *****\n");
    printf("*************************************************\n");
    printf("*************************************************\n");
    printf("*****         Please select operation       *****\n");
    printf("*****        1.parking lot information      *****\n");
    printf("*****        2.enter the parking lot        *****\n");
    printf("*****        3.leave the parking lot        *****\n");
    printf("*****        4.exit system                  *****\n");
    printf("*************************************************\n");
    printf("*************************************************\n");
}

void do_oper(sqlite3 * park)
{
	int input,num;
	int ret;
	int ret_time;
	int stay_time;
    do
	{
		menu();
		printf("please select operation:\n");
		scanf("%d",&input);
		switch(input)
		{
			case 1:
				ret = view_park(park);//查看停车信息；
				if (SQLITE_OK != ret)
				{
				    printf("view park information error!%s\n",sqlite3_errmsg(park));
				}
				break;
			case 2:
				ret = insert_park(park,&ret_time);//进入车位；
				if (SQLITE_OK == ret)
				{
				    printf("enter park success!\n");
				}
				break;
			case 3:
				printf("please select exit stall:\n");
				scanf("%d",&num);
				ret = delete_park(park,num,ret_time,&stay_time);
				if (SQLITE_OK == ret)
				{
					count_money(park,num,stay_time);//计费；
				}
				break;
			case 4:
				exit(1);
				break;
			default :
				printf("input error!please input again!\n");
				break;
		}
	
	}
	while(input);
}

int main()
{
	int ret;
	sqlite3 * park;
	ret = sqlite3_open("park.db",&park);//创建park.db；
    if (SQLITE_OK != ret)
	{
	    printf("open datebase fail!%s\n",sqlite3_errmsg(park));
		exit(-1);
	}

	if (SQLITE_OK == create_park(park))
	{
	    printf("create park success!\n");
		create_stall(park);   //创建停车位；
		do_oper(park);       //进行操作；
	}
	else
	{
	    exit(-1);
	}

	return 0;
}
