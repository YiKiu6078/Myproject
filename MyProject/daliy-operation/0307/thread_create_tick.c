#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

int ticket = 10;

void *sell_ticket1(void)
{
    while(1)
	{
		if(ticket > 0)
		{
			sleep(1);
			printf("sell ticket--> chool ticket:%d\n",--ticket);
		}
		else
		{
			break;
		}
	}
	return NULL;
}

void *sell_ticket2(void)
{

	while(1)
	{
		    if(ticket > 0)
		    {
			sleep(1);
			  printf("sell ticket--> chool ticket:%d\n",--ticket);
		    }
		    else
		    {
			    break;
		    }
	}
}

void *sell_ticket3(void)
{

	while(1)
	{
		    if(ticket > 0)
		    {
			sleep(1);
			  printf("sell ticket--> chool ticket:%d\n",--ticket);
		    }
		    else
		    {
			    break;
		    }
		
	}
	return NULL;
}

int main()
{
    int i=0, ret=0;
    pthread_t id1,id2,id3;

    ret = pthread_create(&id1, NULL, (void*)sell_ticket1, NULL);
     ret = pthread_create(&id2, NULL, (void*)sell_ticket1, NULL);
    ret = pthread_create(&id3, NULL, (void*)sell_ticket1, NULL);

    
    pthread_join(id1, NULL);
	printf("id1 exit!\n");
    pthread_join(id2, NULL);
	printf("id2 exit!\n");
    pthread_join(id3, NULL);
	printf("id3 exit!\n");
    
    return 0;
}
