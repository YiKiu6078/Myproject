#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 16
#define OVER -1


struct number
{
	int buffer[BUFFER_SIZE];
  	pthread_mutex_t lock;
	pthread_cond_t notfull;
	pthread_cond_t notempty;
	int readpos,writepos;
}NUM;

void init(struct number * number)
{
    pthread_mutex_init(&number->lock,NULL);
	pthread_cond_init(&number->notfull,NULL);
	pthread_cond_init(&number->notempty,NULL);
	number->readpos = 0;
	number->writepos = 0;
}

int put(struct number * p,int num)
{
    pthread_mutex_lock(&p->lock);
	if ((p->writepos + 1) % BUFFER_SIZE == p->readpos)
	{
	    printf("shelf is full!\n");
		pthread_cond_wait(&p->notfull,&p->lock);
	}
	p->buffer[p->writepos] = num;
	p->writepos++;
	if (p->writepos >= BUFFER_SIZE)
	{
	    p->writepos = 0;
	}
    pthread_cond_signal(&p->notempty);
	pthread_mutex_unlock(&p->lock);
}

int get(struct number * c)
{
    pthread_mutex_lock(&c->lock);

	if (c->writepos == c->readpos)
	{
		printf("shelf is empty!\n");
		pthread_cond_wait(&c->notempty,&c->lock);
	}
	int data = c->buffer[c->readpos];
	c->readpos++;
	if (c->readpos >= BUFFER_SIZE)
	{
	    c->readpos = 0;
	}
	pthread_cond_signal(&c->notfull);
	pthread_mutex_unlock(&c->lock);
	return data;
}

void *produ()
{
    int n;
	for (n = 0;n < 20;n++)
	{
	    printf("put %d ---->\n",n+1);
		put(&NUM,n+1);
	}

	put(&NUM,OVER);
	return NULL;
}

void *custom()
{
	int d;
    while (1)
	{
	    d = get(&NUM);
		if (d == OVER)
		{
		    break;
		}
		printf("<---- %d get\n",d);
	}
	return NULL;
}

int main()
{
    pthread_t ptid_p,ptid_c;
	int ret;
	init(&NUM);
	ret = pthread_create(&ptid_p,NULL,(void *)produ,NULL);
	if (ret != 0)
	{
	    perror("create thread error");
		exit(-1);
	}
	ret = pthread_create(&ptid_c,NULL,(void *)custom,NULL);
	if (ret != 0)
	{
	    perror("create thread error");
		exit(-1);
	}
	pthread_join(ptid_p,NULL);
	pthread_join(ptid_c,NULL);
	return 0;
}
