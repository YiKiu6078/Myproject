#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
 
#define ALL 10
 
void creat_table(sqlite3 * db)            //创建表，记录车位信息
{
	char *sql;
	char *errmsg;
	int ret;
 
	sql = "create table if not exists mytable (id integer primary key,name text,entertm integer,exittm integer,stall text,entertime text,exittime text);";
 
	ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		printf("create table fail!:%s\n",errmsg);
		exit(-1);
	}
}
 
void creat_new(sqlite3 * db)             //创建新表，保存该停车场的所有停车记录
{
	char *sql;
	char *errmsg;
	int ret;
 
	sql = "create table if not exists newtable (id integer,name text,stall text,entertime text,exittime text);";
 
	ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		printf("create table fail!:%s\n",errmsg);
		exit(-1);
	}
}
 
void insert_init(sqlite3 * db)                  //对创建的车位进行初始化
{
	int i;
	int j = 0;
	for(i = 0;i < ALL; i++)
	{
		int ret;
		char *sql;
		char *errmsg;
 
		sql="insert into mytable(id,name,entertm,exittm,stall,entertime,exittime) values(NULL,'no',NULL,NULL,'no','no','no');";
		ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
		if(ret != SQLITE_OK)
		{
			printf("insert fail!%s\n",errmsg);
			exit(-1);
		}
	}
}
 
void insert_value(sqlite3* db)                    //车主选择位置自由停车
{
	int ret,a;
	char sql[100];
	char *errmsg;
	char name[10];
	time_t t;
 
	printf("输入车牌号:\n");
	scanf("%s",name);
	printf("选择车位:\n");
	scanf("%d",&a);
 
	t = time(NULL);
	struct tm *tb;
	tb = localtime(&t);
 
	sprintf(sql,"update mytable set name = '%s',entertm = %d,stall = 'parking',entertime = '%d.%d.%d %d:%d:%d' where id = %d;",name,t,tb->tm_year+1900,tb->tm_mon+1,tb->tm_mday,tb->tm_hour,tb->tm_min,tb->tm_sec,a);
 
	ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		printf("insert fail!%s\n",errmsg);
		exit(-1);
	}
}
 
void select_all(sqlite3 *db)                  //查看该停车场的车位状况
{
	int ret;
	int i;
	int row = 0;
	int column = 0;
	char * sql;
	char ** presult;
	char *errmsg;
 
	sql = "select id,name,stall from mytable;";
 
	ret = sqlite3_get_table(db,sql,&presult,&row,&column,&errmsg);
	if(ret != SQLITE_OK)
	{
		printf("select fail:%s\n",errmsg);
		exit(-1);
	}
 
	for(i = 0;i < (ALL + 1) * column;i++)
	{
		printf("%15s",presult[i]);
		if((i + 1)%column == 0)
		{
			printf("\n");
		}
		if((i + 1) == column)
		{
			printf("---------------------------------------------------------\n");
		}
	}
}
 
void update_exittm(sqlite3 *db)               //离开车位，计算费用，更新车位信息
{
	int ret1,ret2,ret3;
	int a,b;
	int row = 0;
	int column = 0;
	char ** presult;
	char sql1[100];
	char sql2[100];
	char sql3[100];
	char * errmsg1;
	char * errmsg2;
	char * errmsg3;
	char name[10];
	time_t t;
	struct tm *td;
 
	printf("输入车牌号:\n");
	scanf("%s",name);
 
	t = time(NULL);
	td = localtime(&t);
 
	sprintf(sql1,"update mytable set exittm = %d,exittime = '%d.%d.%d %d:%d:%d' where name = '%s';",t,td->tm_year+1900,td->tm_mon+1,td->tm_mday,td->tm_hour,td->tm_min,td->tm_sec,name);
	ret1 = sqlite3_exec(db,sql1,NULL,NULL,&errmsg1);           //离开车位
	if(ret1 != SQLITE_OK)
	{
		printf("update fail:%s\n",errmsg1);
		exit(-1);
	}
 
	sprintf(sql3,"select entertm,exittm from mytable where name like '%s';",name);
 
	ret3 = sqlite3_get_table(db,sql3,&presult,&row,&column,&errmsg3);
	if(ret3 != SQLITE_OK)
	{
		printf("select fail :%s\n",errmsg3);
		exit(-1);
	}
 
	sprintf(sql3,"insert into newtable(id,name,entertime,exittime) select id,name,entertime,exittime from mytable where name like '%s';",name);
	sqlite3_exec(db,sql3,NULL,NULL,&errmsg1);         //将该车的停车信息保存到新表中
 
	a = atoi(presult[2]);
	b = atoi(presult[3]);
 
	printf("总费用：%d元\n",(b-a)/3600*2);           //计算费用
 
	sprintf(sql2,"update mytable set stall = 'no',name = 'no',entertime = 'no' where name = '%s';",name);
	ret2 = sqlite3_exec(db,sql2,NULL,NULL,&errmsg2);
	if(ret2 != SQLITE_OK)
	{
		printf("delete fail:%s\n",errmsg2);
		exit(-1);
	}
 
}
 
void select_name(sqlite3 * db)                   //按照车牌信息查找该车的停车记录
{
	int ret,i;
	int row = 0;
	int column = 0;
	char ** presult;
	char sql[100];
	char *errmsg;
	char name[20];
 
	while(1)
	{
		printf("输入车牌号:(q quit)\n");
		scanf("%s",name);
		if(strcmp(name,"q") == 0)
			return;
		sprintf(sql,"select id,name,entertime,exittime from newtable where name like '%s';",name);
 
		ret = sqlite3_get_table(db,sql,&presult,&row,&column,&errmsg);
		if(ret != SQLITE_OK)
		{
			printf("select fail :%s\n",errmsg);
			exit(-1);
		}
 
		for(i = 0;i < (row + 1) * column;i++)
		{
			printf("%20s",presult[i]);
			if((i + 1)%column == 0)
			{
				printf("\n");
			}
			if((i + 1) == column)
			{
				printf("-------------------------------------------------------------------------------\n");
			}
		}
	}
}
 
void select_newall(sqlite3 *db)                     //查看该停车场的所有停车记录
{
	int ret;
	int i;
	int row = 0;
	int column = 0;
	char * sql;
	char ** presult;
	char *errmsg;
 
	sql = "select id,name,entertime,exittime from newtable;";
 
	ret = sqlite3_get_table(db,sql,&presult,&row,&column,&errmsg);
	if(ret != SQLITE_OK)
	{
		printf("select fail:%s\n",errmsg);
		exit(-1);
	}
 
	for(i = 0;i < (row + 1) * column;i++)
	{
		printf("%20s",presult[i]);
		if((i + 1)%column == 0)
		{
			printf("\n");
		}
		if((i + 1) == column)
		{
			printf("-----------------------------------------------------------------------------------\n");
		}
	}
}
 
void menu()
{
	printf("\n**************************\n");
	printf("** 1)查看空位 ** 2)停车 **\n");
	printf("** 3)离开交费 ** 4)退出 **\n");
	printf("**     5)管理员系统     **\n");
	printf("**  　收费标准２￥/h 　 **\n");
	printf("**  　  30分钟免费   　 **\n");
	printf("**************************\n\n");
}
 
int main()
{
	int ret,i;
	int a = 0;
	int b,c;
	sqlite3 *db;
 
	ret = sqlite3_open("park.db",&db);
	if(ret != SQLITE_OK)
	{
		printf("open fail!\n");
		exit(-1);
	}
	creat_table(db);
	creat_new(db);
 
	insert_init(db);
	while(a != 4)
	{
		menu();
		printf("选择操作：");
		scanf("%d",&a);
		switch(a)
		{
			case 1:select_all(db);break;
			case 2:insert_value(db);break;
			case 3:update_exittm(db);break;
			case 5:{
					   printf("输入管理员密码(123456)：\n");
					   scanf("%d",&c);
					   if(c == 123456)
					   {
					   b = 0;
					   while(b != 3)
					   {
						   printf("1)查看所有停车记录 2)查找车辆停车信息 3)退出\n");
						   scanf("%d",&b);
						   switch(b)
						   {
							   case 1:select_newall(db);break;
							   case 2:select_name(db);break;
						   }
					   }
					   }
					   else
						   printf("没有权限！\n");
				   }break;
		}
	}
	sqlite3_close(db);
 
    return 0;
}
