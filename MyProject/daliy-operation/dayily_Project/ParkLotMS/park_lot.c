#include "park_lot.h"


int create_park(sqlite3 * park)
{
    char *sql = NULL;
	char *errmsg = NULL;
	int i;
	int ret;

	sql = "create table if not exists park (Stall integer primary key,PlateNumber text,EnterTime text,ExitTime text);";
	ret = sqlite3_exec(park,sql,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
		printf("create park table fail!%s\n",errmsg);
	    return -1;
	}

	return SQLITE_OK;
}

int create_stall(sqlite3 * park)
{
    char * sql = NULL;
	char * errmsg = NULL;
	char ** ret_val = NULL;
	char stall[100];
	int nrow_count,ncol_count;
	int i,ret;
   
	sql = "select * from park;";
	sqlite3_get_table(park,sql,&ret_val,&nrow_count,&ncol_count,&errmsg);
	while(nrow_count != PARK_MAX)
	{
		ret = sqlite3_get_table(park,sql,&ret_val,&nrow_count,&ncol_count,&errmsg);
		for (i = 1; i <= PARK_MAX;i++)
	 	{
	    	sprintf(stall,"insert into park (Stall,PlateNumber,EnterTime,ExitTime) values (%d,NULL,NULL,NULL);",i);
			if (SQLITE_OK != (sqlite3_exec(park,stall,NULL,NULL,&errmsg)))
			{
		    	printf("insert stall fail!%s\n",errmsg);
			}
		}
	}
}

int view_park(sqlite3 * park)
{
    char * sql = NULL;
	char * errmsg = NULL;
	char ** ret_val = NULL;
	int nrow_count,ncol_count;
	int i,ret;

	sql = "select * from park;";
	ret = sqlite3_get_table(park,sql,&ret_val,&nrow_count,&ncol_count,&errmsg);
	if (SQLITE_OK != ret)
	{
	    printf("select error!%s\n",errmsg);
		sqlite3_free_table(ret_val);
		return -1;
	}
	else
	{
	    for (i = 0;i < (nrow_count + 1) * ncol_count;i++)
		{
		    printf("%15s",ret_val[i]);
			if (0 == (i + 1) % ncol_count)
			{
		   		 printf("\n");
			}
		}
	}
	sqlite3_free_table(ret_val);
	return SQLITE_OK;
}

int read_enter_time(sqlite3 * park,int num)
{
    char sql[50];
	char * errmsg = NULL;
	char ** ret_val = NULL;
	int nrow,ncol;
	char * pch = NULL;
	int a;

	sprintf(sql,"select * from park where stall = %d;",num);
	int ret = sqlite3_get_table(park,sql,&ret_val,&nrow,&ncol,&errmsg);
	printf("ret_val[6] = %s\n",ret_val[6]);
	pch = strtok(ret_val[6],":");
	a = atoi(ret_val[6]);
	return a;
}

int insert_park(sqlite3 * park,int * ret_time)
{
    char sql[SQL_MAX];
	char * errmsg = NULL;
	char PN[100];
	int seconds1;
	int ret;
	int num;
	printf("please select stall:\n");
	scanf("%d",&num);
	printf("please input PlateNumber:\n");
	scanf("%s",PN);
	time_t t = time(NULL);
	struct tm * tb;
	tb = localtime(&t);
	seconds1 = (tb->tm_hour)*3600 + (tb->tm_min)*60 + (tb->tm_sec);
	*ret_time = seconds1;
	sprintf(sql,"update park set PlateNumber = '%s',EnterTime = '%d:%d:%d' where stall = %d;",PN,tb->tm_hour,tb->tm_min,tb->tm_sec,num);
	ret = sqlite3_exec(park,sql,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
	    printf("enter park error!%s\n",errmsg);
		return -1;
	}
//	read_enter_time(park,num);
	return SQLITE_OK;
}

int display(sqlite3 * park,int num)
{
    char sql[50];
	char * errmsg = NULL;
	char ** presult = NULL;
	int nrow,ncol;
	int ret,i;

	sprintf(sql,"select * from park where stall = %d;",num);
    ret = sqlite3_get_table(park,sql,&presult,&nrow,&ncol,&errmsg);
	if (SQLITE_OK != ret)
	{
	    printf("select error!%s\n",errmsg);
		sqlite3_free_table(presult);
		return -1;
	}
	else
	{
	    for (i = 0;i < (nrow + 1) * ncol;i++)
		{
		    printf("%15s",presult[i]);
			if (0 == (i + 1) % ncol)
			{
		   		 printf("\n");
			}
		}
	}
	sqlite3_free_table(presult);
	return SQLITE_OK;
}

int delete_park(sqlite3 * park,int num,int ret_time,int * stay_time)
{
    char sql1[SQL_MAX];
    char sql2[SQL_MAX];
	char * errmsg = NULL;
	char * errmsg2 = NULL;
//	char ** ret_val;
//	int nrow,ncol;
	int ret;
//	int a,b;

	int seconds2;
	time_t t = time(NULL);
	struct tm * tb;
	tb = localtime(&t);
	seconds2 = (tb->tm_hour)*3600 + (tb->tm_min)*60 + (tb->tm_sec);
	*stay_time = seconds2 - ret_time;
	sprintf(sql1,"update park set ExitTime = '%d:%d:%d' where stall = %d;",tb->tm_hour,tb->tm_min,tb->tm_sec,num);
	ret = sqlite3_exec(park,sql1,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
	    printf("enter park error!%s\n",errmsg);
		return -1;
	}
	printf("your stall inforrmation is:\n");
	if ((display(park,num)) == SQLITE_OK)
	{
	    printf("exit success!\n");
	}

//	memset(sql,0,sizeof(sql));
	sprintf(sql2,"update park set PlateNumber = NULL,EnterTime = NULL,ExitTime = NULL where stall = %d;",num);
	ret = sqlite3_exec(park,sql2,NULL,NULL,&errmsg2);
	if(SQLITE_OK != ret)
	{
	    printf("update error!%s",errmsg2);
		return -1;
	}
	return SQLITE_OK;
}

void count_money(sqlite3 * park,int num,int stay_time)
{
    float price = stay_time * 0.5;
	printf("Price : 0.5元/s,your stay time is %d s\n",stay_time);
	printf("please pay for %0.2f 元\n",price);
    printf("Welcom to come agin\n");

}




