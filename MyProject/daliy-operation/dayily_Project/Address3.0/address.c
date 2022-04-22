#include "address.h"
int create_address(sqlite3 * adr)
{
    char *sql = NULL;
    char *errmsg = NULL;
    int ret;

    sql = "create table if not exists address(id integer primary key,name text,sex text,age integer,number text,location text);";
    ret = sqlite3_exec(adr,sql,NULL,NULL,&errmsg);
    if (SQLITE_OK != ret)
    {
        printf("create address error ! %s\n",errmsg);
        return -1;
    }
    return SQLITE_OK;
}

int insert_scord(sqlite3 * adr)
{
    int id,age,length;
	char number[NUM_SIZE];
    char name[NAME_SIZE];
    char sex[SEX_SIZE];
    char location[ADR_SIZE];
    char sql[SQL_SIZE];
    char * errmsg = NULL;

    printf("please input contact information !\n");
    printf("please input id:\n");
    scanf("%d",&id);
    printf("please input name:\n");
    scanf("%s",name);
    printf("please input sex:\n");
    scanf("%s",sex);
    printf("please input age:\n");
    scanf("%d",&age);
    printf("please input number:\n");
    scanf("%s",number);
	while ((length = strlen(number)) != 11)
	{
	    printf("the length of number is fail!please input eleven digit!\n");
		scanf("%s",number);
	}
    printf("please input location:\n");
    scanf("%s",location);
    sprintf(sql,"insert into address (id,name,sex,age,number,location) values (%d,'%s','%s',%d,'%s','%s');",id,name,sex,age,number,location);
    int ret = sqlite3_exec(adr,sql,NULL,NULL,&errmsg);
    if (SQLITE_OK != ret)
    {
        printf("insert scord error!%s\n",errmsg);
        return -1;
    }
    return SQLITE_OK;
}

int delete_scord(sqlite3 * adr)
{
	int id;
	int ret;
	char sql[SQL_SIZE];
	char * errmsg;

	printf("please input linkman's  id :\n");
	scanf("%d",&id);

	sprintf(sql,"delete from address where id = %d ;",id);
	ret = sqlite3_exec(adr,sql,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
	    printf("delete scord error ! %s\n",errmsg);
		return -1;
	}
	return SQLITE_OK;
}

int change_name(sqlite3 * adr,int id)
{
    char name[NAME_SIZE];
	char * errmsg = NULL;
	char sql[SQL_SIZE];
	int ret;

	printf("please input Modified name:\n");
	scanf("%s",name);

	sprintf(sql,"update address set name='%s' where id=%d;",name,id);
	ret = sqlite3_exec(adr,sql,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
	    printf("chang name error!%s\n",errmsg);
		return -1;
	}
	return SQLITE_OK;
}

int chang_sex(sqlite3 * adr,int id)
{
	char sex[SEX_SIZE];
	char * errmsg = NULL;
	char sql[SQL_SIZE];
	int ret;

	printf("please input Modified sex:\n");
	scanf("%s",sex);

	sprintf(sql,"update address set sex='%s' where id=%d;",sex,id);
	ret = sqlite3_exec(adr,sql,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
	    printf("chang sex error!%s\n",errmsg);
		return -1;
	}
	return SQLITE_OK;
}

int chang_age(sqlite3 * adr,int id)
{
	int age;
	char * errmsg = NULL;
	char sql[SQL_SIZE];
	int ret;

	printf("please input Modified age:\n");
	scanf("%d",&age);

	sprintf(sql,"update address set age=%d where id=%d;",age,id);
	ret = sqlite3_exec(adr,sql,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
	    printf("chang age error!%s\n",errmsg);
		return -1;
	}
	return SQLITE_OK;
}

int chang_number(sqlite3 * adr,int id)
{
	char number[NUM_SIZE];
	char * errmsg = NULL;
	char sql[SQL_SIZE];
	int ret,length;

	printf("please input Modified number:\n");
	scanf("%s",number);
	while ((length = strlen(number)) != 11)
	{
	    printf("the length of number is fail!please input eleven digit!\n");
		scanf("%s",number);
	}

	sprintf(sql,"update address set number='%s' where id=%d;",number,id);
	ret = sqlite3_exec(adr,sql,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
	    printf("chang number error!%s\n",errmsg);
		return -1;
	}
	return SQLITE_OK;
}

int chang_location(sqlite3 * adr,int id)
{
	char location[ADR_SIZE];
	char * errmsg = NULL;
	char sql[SQL_SIZE];
	int ret;

	printf("please input Modified location:\n");
	scanf("%s",location);

	sprintf(sql,"update address set location='%s' where id=%d;",location,id);
	ret = sqlite3_exec(adr,sql,NULL,NULL,&errmsg);
	if (SQLITE_OK != ret)
	{
	    printf("chang location error!%s\n",errmsg);
		return -1;
	}
	return SQLITE_OK;
}

int update_scord(sqlite3 * adr)//修改联系人记录
{
    int id;
	int num,ret;
	printf("please input update linkman id:\n");
	scanf("%d",&id);

    do
	{
		printf("please input select num:\n");
		printf("1.name 2.sex 3.age 4.number 5.location 0.quit select\n");
		scanf("%d",&num);
		switch(num)
		{
		    case 1:
				ret = change_name(adr,id);
				if (SQLITE_OK == ret)
				{
				    printf("Modified name success!\n");
				}
				break;
			case 2:
				ret = chang_sex(adr,id);
				if (SQLITE_OK == ret)
				{
				    printf("Modified sex success!\n");
				}
				break;
			case 3:
				ret = chang_age(adr,id);
				if (SQLITE_OK == ret)
				{
				    printf("Modified age success!\n");
				}
				break;
			case 4:
				ret = chang_number(adr,id);
				if (SQLITE_OK == ret)
				{
				    printf("Modified number success!\n");
				}
				break;
			case 5:
				ret = chang_location(adr,id);
				if (SQLITE_OK == ret)
				{
				    printf("Modified location success!\n");
				}
				break;
			default :
				printf("input error!please select again!\n");
				break;
		}
		if (0 == num)
		{
		    printf("exit...\n");
		}
	}
	while(num);
}

int inquire_scord(sqlite3 * adr)
{
    int id,i;
    int nrow_count,ncol_count;  //定义行数，列数，（行数不包含表头所在的行）；
    int ret;
    char ** ret_val = NULL;
    char * errmsg = NULL;
    char sql[SQL_SIZE];

    printf("please input linkman id:\n");
    scanf("%d",&id);

    sprintf(sql,"select * from address where id = %d;",id);
    ret = sqlite3_get_table(adr,sql,&ret_val,&nrow_count,&ncol_count,&errmsg); //使用get_table作为查询接口，ret_val为函数返回值；
    if (SQLITE_OK == ret)
    {
        printf("nrow_count = %d,ncol_count = %d\n",nrow_count,ncol_count);
	    for (i = 0;i < (nrow_count + 1) * ncol_count;i++)  //i < 整个表格里数量；
	    {
			if ((i + 1) % ncol_count == (ncol_count - 1))  //如果是number 这一列将字符串输出宽度扩大15；
			{
	            printf("%15s",ret_val[i]);
			}
		    else if ((i + 1) % ncol_count == 0)   //如果是最后一列，则将宽度扩大为15，并且下一行换行；
		    {
	            printf("%15s",ret_val[i]);
		        printf("\n");
		    }
	        else
			{
			    printf("%10s",ret_val[i]);
			}
	    }
    }
    else
    {
        printf("inquire scord error! %s\n",errmsg);
	    sqlite3_free_table(ret_val);
	    return -1;
    }
    sqlite3_free_table(ret_val);
    return SQLITE_OK;
}

int inquire_all_scord(sqlite3 * adr)
{
    char * sql = NULL;
    int nrow_count,ncol_count;
    int ret,i;
    char ** ret_val = NULL;
    char * errmsg = NULL;
	
	sql = "select * from address ;";
    ret = sqlite3_get_table(adr,sql,&ret_val,&nrow_count,&ncol_count,&errmsg);
    if (SQLITE_OK == ret)
    {
        printf("nrow_count = %d,ncol_count = %d\n",nrow_count,ncol_count);
	    for (i = 0;i < (nrow_count + 1) * ncol_count;i++)
	    {
			if ((i + 1) % ncol_count == (ncol_count - 1))
			{
	            printf("%15s",ret_val[i]);
			}
		    else if ((i + 1) % ncol_count == 0)
		    {
	            printf("%15s",ret_val[i]);
		        printf("\n");
		    }
	        else
			{
			    printf("%10s",ret_val[i]);
			}
	    }
    }
    else
    {
        printf("inquire scord error! %s\n",errmsg);
	    sqlite3_free_table(ret_val);
	    return -1;
    }
    sqlite3_free_table(ret_val);
    return SQLITE_OK;
}


