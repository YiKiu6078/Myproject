/***log***/

#include "myhead.h"
int flag = 0;
#define OK 0 
#define SQLITE_OK 0


int logg(int id, int fd, struct message Msg,Node *head)
{
	int sendcnt = 0;
	printf(GREEN"正在进行登录...\n");
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
			//input(db,fd,Msg);	
			find(db,id,fd,Msg);
			
			
			if(flag == 1)
			{
				online_check(*head,fd,Msg.id,&Msg);
				if(Msg.backid == 1)
				{
					online_insert(head,fd,Msg.id,Msg.name);
				}
					online_display(*head,fd,Msg.id);
				
				
				
				
			}
			else
			{
				printf(RED"密码错误！登录失败");
				printf(DEFAULT);
			}
				
				//		}
//		while(1);
	}
	return 0;
}




/**********查找模式************/
void find(sqlite3 *db,int id, int fd, struct message Msg)
{
	printf(GREEN"正在登录load1......\n");
	printf(DEFAULT);

	int in, ret, i;
	char sql[1024], who[20], name[20],key[20];
	char *errmsg;
	char sel;
	char **result;
	int row, column;

	printf("Msg.id=%s\n",Msg.id);
	strcpy(who, Msg.id);
	//printf("who=%s\n",who);

		sprintf(sql, "select key from reg where id = %d;",atoi(who));
		
		//printf("atoiwho=%d\n",atoi(who));

		ret = sqlite3_get_table(db,sql,&result,&row,&column,&errmsg);	
		if(SQLITE_OK !=ret)
		{
			printf("error:%s\n",errmsg);
			exit(1);
		}
		
		//printf("row=%d,column=%d\n",row,column);
		
		if(row == 0)
		{
			printf("未找到该账号:\n");
		}
		else
		{
			//printf("row=%d\n",row);
			printf("密码=%s\n",result[row]);
			printf("input key=%s\n",Msg.key);
			
			if(strcmp(Msg.key,result[row]) == 0)
			{
				flag = 1;
			}
			else
			{
				flag = 0;
			}
		}
	
	
	


	printf(GREEN"登录成功，正在返回......\n");
	printf(DEFAULT);

}





