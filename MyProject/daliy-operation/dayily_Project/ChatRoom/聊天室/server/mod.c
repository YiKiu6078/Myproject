/******mod******/

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
int Mod(int id, int fd, struct message Msg)
{
	printf(GREEN"正在进行重置密码...\n");
	printf(DEFAULT);
	sqlite3 *db;
	int rc;
	int in;
	rc = open_db(&db);
	if (rc == OK)
	{
		create_table(db);

		input1(db,fd,Msg);	


	}
	return 0;
}


/*************数据库输入*************/
void input1(sqlite3 *db,int fd,struct message Msg)
{
	printf(GREEN"正在重置load......\n");
	printf(DEFAULT);
	
	char sql[100];
	char *errmsg;
	int ret;
	char key1[20],id[20];
 		

//	printf("%d\n",strlen(Msg.key));................
	strcpy(id,"0");
	
	strcpy(key1,"0");
	
	strcpy(id,Msg.id);
	strcpy(key1,Msg.key);
	//printf("nnnnnnnnnnnnnnnnnn%s\n",name);
	


	sprintf(sql,"update reg set key='%s' where id=%d;",key1,atoi(id));
	ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if(ret != SQLITE_OK)
	{
		printf("插入数据失败:%s\n", errmsg);
		exit (-1);	
	}
	printf(GREEN"密码重置成功，正在返回......");
	printf(DEFAULT);
}











