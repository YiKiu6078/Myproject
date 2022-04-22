#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct val
{
    int num;
	char *str;
};

void *ret_val(void *msg)
{
    struct val * test = (struct val *)msg;
	test->num = 6;
	strcpy(test->str,"what's up!");
	return (void *) test;
}

int main()
{
    pthread_t ptid;
	int ret;
	void *rv;
	struct val * v;
	struct val * tmp;

	v = (struct val *)malloc(sizeof(struct val));
	tmp = (struct val *)malloc(sizeof(struct val));

	tmp->num = 8;
	tmp->str = "chijing";
	pthread_create(&ptid,NULL,ret_val,(void *)tmp);
/*	if(ret != 0)
	{
	    perror("create pthread error!\n");
		exit(-1);
	}
*/
	ret = pthread_join(ptid,&rv);
	if (ret != 0)
	{
	    perror("joined error!\n");
		exit(-1);
	}
	v = (struct val *)rv;
//	printf("rv->num = %d\n",v->num);
//	printf("rv->str = %s\n",v->str);

	printf("tmp.num = %d\n",tmp->num);
	printf("tmp.str = %s\n",tmp->str);
	return 0;
}
