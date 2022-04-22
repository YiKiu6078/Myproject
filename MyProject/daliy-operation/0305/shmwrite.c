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
#include <sys/shm.h>
#include "shmdata.c"
#include <string.h>

#define BUFFSIZE 2048

int main()
{
    int running = 1;
    void *shm = NULL;
    struct shared_use_st * shared = NULL;
    char buffer[BUFFSIZE + 1];
    int shmid;
    
    shmid = shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);

    if(shmid == -1)
    {
        fprintf(stderr,"shmget failed\n");
        exit(EXIT_FAILURE);
    }
    shm = shmat(shmid,0,0);
    if(shm == (void*)-1)
    {
        fprintf(stderr,"shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("\n memary attached at %d\n",(int)shm);

    shared = (struct shared_use_st *)shm;
    //shared->written = 0;
    while(running)
    {
        while(shared->written == 1)
        {
            sleep(1);
            printf("waitting...\n");
        }
        printf("Enter some text:\n");
        fgets(buffer,BUFFSIZE,stdin);
        strncpy(shared->text,buffer,TEXT_SZ);
        /*if(shared->written != 0)
        {
            printf("you wrote : %s\n",shared->text);
            sleep(rand()%3);*/
            shared->written = 1;
            if(strncmp(shared->text,"end",3) == 0)
                running = 0;
       // }
       // else
       //     sleep(1);
    }
    if(shmdt(shm) == -1)
    {
        fprintf(stderr,"shmdt failed\n");
        exit(EXIT_FAILURE);
    }
   /* if(shmctl(shmid,IPC_RMID,0) == -1)
    {
        fprintf(stderr,"stmctl failed\n");
        exit(EXIT_FAILURE);
    }*/
    sleep(2);
    exit(EXIT_SUCCESS);
    return 0;
}

