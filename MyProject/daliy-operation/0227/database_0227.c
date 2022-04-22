/*****************************************************
copyright (C), 2014-2015, Lighting Studio. Co.,     Ltd. 
File name：
Author：Jerey_Jobs    Version:0.1    Date: 
Description：
Funcion List: 
*****************************************************/

#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

int create_table(sqlite3 * pdb)
{
	char *sql = NULL;
	char *errmsg = NULL;
	int ret;

	sql = "create table if not exists mytable (id integer primary key,name text);";

	ret = sqlite3_exec(pdb,sql,NULL,NULL,&errmsg);

	if(SQLITE_OK != ret)
	{
		printf("create table error! %s\n",errmsg);

		return -1;
	}
	else
	{
		return SQLITE_OK;
	}
}

int insert_record(sqlite3 * pdb)
{
	//char *sql = NULL;
	char sql[100];
	char *errmsg = NULL;
	int ret;
	int id;
	char name[20];

	printf("please input in and name :\n");
	scanf("%d",&id);
	scanf("%s",name);

	//sql = "insert into mytable (id,name) values (NULL,'chen');";
	sprintf(sql,"insert into  mytable (id,name) values (%d,'%s');",id,name);

	ret = sqlite3_exec(pdb,sql,NULL,NULL,&errmsg);

	if(SQLITE_OK != ret)
	{
		printf("insert record 1 error! %s\n",errmsg);

		return -1;
	}

#if 0

	sql = "insert into mytable (id,name) values (NULL,'zhang');";

	ret = sqlite3_exec(pdb,sql,NULL,NULL,&errmsg);

	if(SQLITE_OK != ret)
	{
		printf("insert record 2 error! %s\n",errmsg);

		return -1;
	}

	sql = "insert into mytable (id,name) values (NULL,'liu');";

	ret = sqlite3_exec(pdb,sql,NULL,NULL,&errmsg);

	if(SQLITE_OK != ret)
	{
		printf("insert record 3 error! %s\n",errmsg);

		return -1;
	}
#endif

	return SQLITE_OK;
}

int display(void * para,int ncol,char * col_val[],char ** col_name)
{
	int i;
	int * flag =  NULL;

	flag = (int *)para;

	if(0 == *flag)
	{
		*flag = 1;
	
		printf("column number is : %d\n",ncol);

    	for(i = 0; i < ncol;i++)
    	{
	    	printf("%10s",col_name[i]);
    	}
    	printf("\n");
	}

	for(i = 0;i < ncol;i++)
	{
		printf("%10s",col_val[i]);
	}

	printf("\n");

	return 0;
}

int inquire_uscb(sqlite3 * pdb)
{
	char *sql = NULL;
	char *errmsg = NULL;
	int ret;
	int flag = 0;

	sql = "select * from mytable;";

	ret = sqlite3_exec(pdb,sql,display,(void *) &flag,&errmsg);

	if(SQLITE_OK != ret)
	{
		printf("select error! %s\n",errmsg);

		return -1;
	}
	else
	{
		return SQLITE_OK;
	}
}

int delete_record(sqlite3 * pdb)
{
	char sql[100];
	char *errmsg = NULL;
	int ret;
	int id;

	printf("please input delete id:\n");
	scanf("%d",&id);

	sprintf(sql, "delete from mytable where id = %d;",id);

	ret = sqlite3_exec(pdb,sql,NULL,NULL,&errmsg);

	if(SQLITE_OK != ret)
	{
		printf("delete error! %s\n",errmsg);

		return -1;
	}
	else
	{
		return SQLITE_OK;
	}
}

int inquire_nocb(sqlite3 *pdb)
{
	char *sql = NULL;
	char ** ret_val = NULL;
	char * errmsg = NULL;
	int nrow;
	int ncol;
	int ret;
	int i;

	sql = "select * from mytable;";

    ret = sqlite3_get_table(pdb,sql,&ret_val,&nrow,&ncol,&errmsg);

	if(SQLITE_OK == ret)
	{
        printf("nrow = %d ncol = %d\n",nrow,ncol);

        for(i = 0; i < (nrow + 1) * ncol;i++)
		{
			printf("%10s",ret_val[i]);

			if((i + 1) % ncol == 0)
			{
				printf("\n");
			}
		}
	}
	else
	{
	    sqlite3_free_table(ret_val);
		
		return -1;
	}

	sqlite3_free_table(ret_val);
}

int main()
{
	sqlite3 *pdb;
	int ret;

	ret = sqlite3_open("mydatabase.db",&pdb);

	if(SQLITE_OK != ret)
	{
		printf("open database fail! %s\n",sqlite3_errmsg(pdb));
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("open database successfully!\n");
	}

    if(SQLITE_OK == create_table(pdb))
	{
		printf("create table success!\n");
	}
	else
	{
		sqlite3_close(pdb);
		return 0;
	}

    if(insert_record(pdb) != 0)
	{
		sqlite3_close(pdb);
		exit(-1);
	}

	inquire_uscb(pdb);

	delete_record(pdb);

	inquire_nocb(pdb);

	sqlite3_close(pdb);

    return 0;
}
