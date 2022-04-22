#include "c_s.h"

int create_table(sqlite3 * db)
{
    char * sql = NULL;
    char * errmsg = NULL;

    sql = "create table if not exists usr_info (count integer primary key,name text,password text);";
    int ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
    if (SQLITE_OK != ret)
    {
        printf("create table error!%s\n",errmsg);
        return SQLITE_NO;
    }
    return SQLITE_OK;
}

void seek_table(sqlite3 * db)
{
	char sql[SQL_SIZE];
	char * errmsg = NULL;
	char ** result = NULL;
	int n_row,n_col;
	int ret,i;
	int count;
	scanf("%d",&count);
//	int account = msg_info->account;
//	ret = is_exist(TNode);
	sprintf(sql,"select * from usr_info where count = %d;",count);
	ret = sqlite3_get_table(db,sql,&result,&n_row,&n_col,&errmsg);
//	printf("1 = %s, 2 = %s\n",result[3],result[4]);
	for (i = 0;i < (n_row + 1) * n_col;i++)
	{
		printf("%10s",result[i]);
		if ((i + 1) % n_col == 0)
		{
		    printf("\n");
		}
	}
}

int main()
{
	sqlite3 * db;  //定义数据库变量
	int ret = sqlite3_open("chat_database.db",&db);
	if (SQLITE_OK != ret)
	{
    	printf("open database error!\n");
    	exit(EXIT_FAILURE);
	}
    //创建表
	if (SQLITE_OK != create_table(db))
	{
    	printf("create table failure!\n");
    	sqlite3_close(db);
    	return 0;
	}
	seek_table(db);
	sqlite3_close(db);
}
