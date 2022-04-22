#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

int ticket = 10;

pthread_mutex_t mutex;


void *sell_ticket1(void)
{
    while(1)
	{
        ret = pthread_mutex_trylock(&mutex);
		if(ticket > 0)
		{
          //  pthread_mutex_lock(&mutex);
		    sleep(1);
			printf("sell ticket--> chool ticket:%d\n",--ticket);
            
		    pthread_mutex_unlock(&mutex);
			//sleep(1);
		}
		else
		{
		     
		    pthread_mutex_unlock(&mutex);
			break;
		}

		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

void *sell_ticket2(void)
{
    int ret;

	while(1)
	{
        ret = pthread_mutex_trylock(&mutex);
		if(ret != EBUSY)
		{
		    if(ticket > 0)
		    {
              //  pthread_mutex_lock(&mutex);
		      sleep(1);
			  printf("sell ticket--> chool ticket:%d\n",--ticket);
            
		      pthread_mutex_unlock(&mutex);
			  //sleep(1);
		    }
		    else
		    {
		     
		        pthread_mutex_unlock(&mutex);
			    break;
		    }

		    pthread_mutex_unlock(&mutex);
		}
	}
}

void *sell_ticket3(void)
{
    int ret;

	while(1)
	{
        ret = pthread_mutex_trylock(&mutex);
		if(ret != EBUSY)
		{
		    if(ticket > 0)
		    {
              //  pthread_mutex_lock(&mutex);
		      sleep(1);
			  printf("sell ticket--> chool ticket:%d\n",--ticket);
            
		      pthread_mutex_unlock(&mutex);
			  //sleep(1);
		    }
		    else
		    {
		     
		        pthread_mutex_unlock(&mutex);
			    break;
		    }

		    pthread_mutex_unlock(&mutex);
		}
	}

	return NULL;
}

int main()
{
    int i=0, ret=0;
    pthread_t id1,id2,id3;
    
   // mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));

    pthread_mutex_init(&mutex,NULL);

    ret = pthread_create(&id1, NULL, (void*)sell_ticket1, NULL);
    ret = pthread_create(&id2, NULL, (void*)sell_ticket1, NULL);
    ret = pthread_create(&id3, NULL, (void*)sell_ticket1, NULL);
    

    
    pthread_join(id1, NULL);
	printf("id1 exit!\n");
    pthread_join(id2, NULL);
	printf("id2 exit!\n");
    pthread_join(id3, NULL);
	printf("id3 exit!\n");

	printf("hello world!\n");
    
    return 0;
}
