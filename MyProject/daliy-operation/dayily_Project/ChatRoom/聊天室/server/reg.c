/***reg***/

#include "myhead.h"
#define OK 0 
#define SQLITE_OK 0
/* int have_flag = 0;
//char ssid = {0};
void create_table(sqlite3 *db);
int open_db(sqlite3 **db);
void input(sqlite3 *db,int fd,struct message Msg);
void find(sqlite3 *db, int id,int fd, struct message Msg);
int displaycb(void *para, int ncolumn, char **columnvalue, char *columnname[]);
 */
int reg(int id, int fd, struct message Msg)
{
	printf(GREEN"正在进行注册...\n");
	printf(DEFAULT);
	sqlite3 *db;
	int rc;
	int in;
	rc = open_db(&db);
	if (rc == OK)
	{
		create_table(db);
//		do
//		{
			input(db,fd,Msg);	
			findreg(db,id,fd,Msg);
//		}
//		while(1);
	}
	return 0;
}


/****************打开数据库********************/
int open_db(sqlite3 **db)
{
	int rc;
	rc = sqlite3_open("reg.db",db);
	if (rc != SQLITE_OK)
	{
		printf("数据库打开失败\n");
		exit(1);
	}
	else
	{
		return OK;
	}
}


/***************新建数据库****************/
void create_table(sqlite3 *db)
{
	int rc;
	char *errmsg;
	rc=sqlite3_exec(db,"create table if not exists reg(id integer primary key autoincrement,name text,key text);",NULL,NULL,&errmsg);
	if (rc != SQLITE_OK)
	{
		printf("数据表创建失败:%s\n",errmsg);
		exit (-1);	
	}
}



/*************数据库输入*************/
void input(sqlite3 *db,int fd,struct message Msg)
{
	printf(GREEN"正在注册load......\n");
	printf(DEFAULT);
	
	char sql[100];
	char *errmsg;
	int ret;
	char name[20],key[20];
 		

//	printf("%d\n",strlen(Msg.key));................
	strcpy(name,"0");
	
	strcpy(key,"0");
	
	strcpy(name,Msg.name);
	strcpy(key,Msg.key);
	//printf("nnnnnnnnnnnnnnnnnn%s\n",name);
	//printf("kkkkkkkkkkkkkkkkkk%s\n",key);


	sprintf(sql,"insert into reg(name,key) values ('%s','%s');",name,key);
	ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if(ret != SQLITE_OK)
	{
		printf("name key 插入数据失败:%s\n", errmsg);
		exit (-1);	
	}
	printf(GREEN"reg注册成功，正在返回......");
	printf(DEFAULT);
}


/**********查找模式************/
void findreg(sqlite3 *db,int id, int fd, struct message Msg)
{
	printf(GREEN"正在注册load1......\n");
	printf(DEFAULT);

	int in, ret, i;
	char sql[100], who[20], name[20],key[20];
	char *errmsg;
	char sel;
	char **result;
	int row, column;

	strcpy(who, Msg.name);
//	printf("cpy:%s\n",who);	

		sprintf(sql, "select id from reg where name = '%s';",who);
//		ret = sqlite3_exec(db, sql, displaycb, NULL, &errmsg);
//	if (have_flag)
//	{
//			if (ret != SQLITE_OK)
//		{
//			printf("数据库查询出错%s\n", errmsg);
//			exit(-1);
//		}
//	}

//	else
//	{
//		printf(RED"未能找到匹配项，正在跳转......\n");
//		printf(DEFAULT);
		//		getchar();
//	}

//	sprintf(sql, "select id from reg where name=%s;",Msg.name);
	ret = sqlite3_get_table(db,sql,&result,&row,&column,&errmsg);	
	if(SQLITE_OK !=ret)
		{
			printf("error:%s\n",errmsg);
			exit(1);
		}
		
		if(row == 0)
		{
			printf("未找到该账号:\n");
		}
		else
		{
	
	
			printf("remember your id-----%s\n",result[row]);
	
//			Msg.id = *((int*)result[row]);
			strcpy(Msg.id,result[row]);
			printf("%s\n",Msg.id);


//			ssid = Msg.id;
			strcpy(ssid,Msg.id);
			printf("ssid%s\n",ssid);
		}

	printf(GREEN"请记住你的登录id，，，正在返回......\n");
	printf(DEFAULT);

}




/**********************显示程序**************************/
/* int displaycb(void *para, int ncolumn, char **columnvalue, char *columnname[])
{
		
	int i;
	have_flag = 0;
	if (ncolumn)
	{
		printf(GREEN"****************查询结果为:****************\n");
		printf(DEFAULT);
		for (i = 0; i < ncolumn; i++)
		{
			printf(YELLOW"%5s:---> ", columnname[i]);
			printf(DEFAULT);
			printf("%2s:\n", columnvalue[i]);
//			ssid = columnvalue[i]; 
//			printf("ssid%d\n",ssid);
		}
		printf("*******************************************\n");
		

		have_flag = 1;
		return OK;
	}
	else
	{
		have_flag = 0;
	}
}
 */

