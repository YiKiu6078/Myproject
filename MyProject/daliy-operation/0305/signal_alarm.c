/*****************************************************
copyright (C), 2014-2015, Lighting Studio. Co.,     Ltd. 
File name：
Author：Jerey_Jobs    Version:0.1    Date: 
Description：
Funcion List: 
*****************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void func(int signo)
{
	if(signo == SIGALRM)
	{
		printf("signal is SIGALRM!\n");
	}
}

int main()
{
	int ret;


	ret = alarm(5);

	signal(SIGALRM,func);

	pause();



	printf("i have been waken up!\n");

    return 0;
}
