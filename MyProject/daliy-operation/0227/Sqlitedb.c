#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define MAX_SQL 100
#define MAX_NAME 20

int create_table(sqlite3 * pdb)
{
    char *sql = NULL;
    char * errmsg = NULL;
	int ret;
	
	sql = "create table if not exists mytable(id integer primary key,name text);";
    ret = sqlite3_exec(pdb,sql,NULL,NULL,&errmsg);
	
	if (SQLITE_OK != ret)
	{
	    printf("create table is error\n");
		return -1;
	}
	else
	{
	    return SQLITE_OK;
	}
}

int insert_scord(sqlite3 * pdb)
{
	char sql[MAX_SQL];
	char * errmsg = NULL;
	int ret;
	int id;
	char name[MAX_NAME];
	printf("please input id and name:\n");
	scanf("%d",&id);
	scanf("%s",name);
	sprintf(sql,"insert into mytable (id,name) values (%d,'%s');",id,name);
	ret = sqlite3_exec(pdb,sql,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
		return -1;
	}
	else
	{
	    return SQLITE_OK;
	}
}

int delete_scord(sqlite3 * pdb)
{
	char sql[MAX_SQL];
	char * errmsg = NULL;
	int ret;
	int id;
	printf("please input delete id\n");
	scanf("%d",&id);
	sprintf(sql,"delete from mytable where id=%d;",id);
	ret = sqlite3_exec(pdb,sql,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
		printf("delete scord error ! %s\n",errmsg);
		return -1;
	}
	else
	{
	    return SQLITE_OK;
	}
}

int display(void * para,int ncol,char * ncol_val[],char ** ncol_name)//回调函数；
{
    int * flag = NULL;
	flag =(int *)para;
	int i;
	if (0 == flag)
	{
		*flag = 1;
		printf("column number is %d\n",ncol);
		for (i = 0;i < ncol;i++)
		{
			printf("%10s",ncol_name[i]);
		}
		printf("\n");
	}
    for (i = 0;i < ncol;i++)
	{
	    printf("%10s",ncol_val[i]);
	}
	printf("\n");
	return 0;
}

int inquire_uscb(sqlite3 * pdb)
{
    char sql[MAX_SQL];
	char * errmsg = NULL;
	int flag = 0;
	int ret;
	int id,num;
  
	printf("please input select num!\n");
	printf("1、select id 2、select all\n");
	scanf("%d",&num);
	if (1 == num)
	{
		printf("please input select id!\n");
		scanf("%d",&id);
	    sprintf(sql,"select * from mytable where id=%d;",id);
	}
	else if (2 == num)
	{
	    sprintf(sql,"select * from mytable;");
	}
	else 
	{
	    printf("input error!");
		return -1;
	}
	ret = sqlite3_exec(pdb,sql,display,(void *)&flag,&errmsg);
	if (SQLITE_OK != ret)
	{
		return -1;
	}
	return SQLITE_OK;
}

int inquire_nocb(sqlite3 * pdb)
{
    char sql[MAX_SQL];
	char * errmsg = NULL;
	char ** ret_val = NULL;
	int ncol_count,nrow_count;
	int num,id;
	int ret;
	int i;

	printf("please input select num!\n");
	printf("1、select id 2、select all\n");
	scanf("%d",&num);
	if (1 == num)
	{
		printf("please input select id!\n");
		scanf("%d",&id);
	    sprintf(sql,"select * from mytable where id=%d;",id);
	}
	else if (2 == num)
	{
	    sprintf(sql,"select * from mytable;");
	}
	else 
	{
	    printf("input error!");
		return -1;
	}
	ret = sqlite3_get_table(pdb,sql,&ret_val,&nrow_count,&ncol_count,&errmsg);
	if (SQLITE_OK == ret)
	{
	    printf("nrow_count = %d,ncol_count = %d\n",nrow_count,ncol_count);
		for (i = 0;i < (nrow_count + 1) * ncol_count;i++)
		{
		    printf("%10s",ret_val[i]);
			if ((i + 1) % ncol_count == 0)
			{
			    printf("\n");
			}
		}
	}
	else
	{
		printf("select error!%s\n",errmsg);
	    sqlite3_free_table(ret_val);
		return -1;
	}
	
	sqlite3_free_table(ret_val);
}

int change_scord(sqlite3 * pdb)
{
    char sql[MAX_SQL];
	char * errmsg = NULL;
	int ret;
	int id;
	char name[MAX_NAME];
	printf("please input id :\n");
	scanf("%d",&id);
	printf("please input change name:\n");
	scanf("%s",name);
	sprintf(sql,"update mytable set nam='%s' where id=%d;",name,id);
	ret = sqlite3_exec(pdb,sql,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
		return -1;
	}
	else
	{
	    return SQLITE_OK;
	}
}

int main()
{
    sqlite3 * pdb;
	int ret = sqlite3_open("new_datebase.db",&pdb);
    if (SQLITE_OK == ret)
	{
	    printf("open mytable is ok!\n");
	}
	else
	{
	    printf("open mytable is error!%s\n",sqlite3_errmsg(pdb));
		exit(EXIT_FAILURE);
	}
	if (SQLITE_OK == create_table(pdb))
	{
	    printf("create table is ok!\n");
	}
	else
    {
	    printf("create table is fail!\n");
		sqlite3_close(pdb);
		return 0;
	}
#if 0
	if (SQLITE_OK == insert_scord(pdb))
	{
	    printf("insert scord success!\n");
	}
	else
	{
	    printf("insert scord error!%s\n",sqlite3_errmsg(pdb));
		exit(EXIT_FAILURE);
	}
#endif

    if (SQLITE_OK != delete_scord(pdb))
	{
		sqlite3_close(pdb);
		exit(EXIT_FAILURE);
	}
	else
	{
	    printf("delete scord success!\n");
	}

    if (SQLITE_OK == change_scord(pdb))
	{
	    printf("change scord success!\n");
	}
	else
	{
	    printf("change scord fail! %s\n",sqlite3_errmsg(pdb));
	}

/*    
    if (SQLITE_OK != inquire_uscb(pdb))
	{
		printf("select fail!\n");
	}
*/  
	if (SQLITE_OK != inquire_nocb(pdb))
	{
	    printf("select fail!\n");
	}
	
	sqlite3_close(pdb);
	return 0;
}
