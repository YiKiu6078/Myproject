/*****************************************************
copyright (C), 2014-2015, Lighting Studio. Co.,     Ltd. 
File name：
Author：Jerey_Jobs    Version:0.1    Date: 
Description：
Funcion List: 
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFFER_SIZE 2048

int main()
{
    pid_t pid;
    int shmid;
    char *shm_addr;
    char flag[]="parent";
    char buff[BUFFER_SIZE];
    
    if((shmid = shmget(IPC_PRIVATE,BUFFER_SIZE,0666)) < 0)
    {
       perror("shmget");
       exit(1);
    }
    else
        printf("create share memory!\n");
    
    if((pid = fork()) < 0 )
    {
        perror("fork");
        exit(1);
    }
    else if(pid == 0)
    {
        if((shm_addr = shmat(shmid,0,0)) == (void *)-1)
        {
            perror("child:shmat\n");
            exit(1);
        }
        else 
            printf("child:Attach shared memory:%p\n",shm_addr);

        while(strncmp(shm_addr,flag,strlen(flag)))
        {
            printf("child: waiting for data...\n");
            sleep(3);
        }

        strcpy(buff,shm_addr + strlen(flag));
        printf("child:shared memory:%s\n",buff);
        
        if(shmdt(shm_addr) < 0)
        {
            perror("child:shmdt");
            exit(1);
        }
        else
            printf("child:detached shared memory\n");
    }
    else
    {
        sleep(1);
        if((shm_addr = shmat(shmid,(void *)0,0)) == (void *)-1)
        {
            perror("parent:shmat\n");
            exit(1);
        }
        else
        {
            printf("parent attach share memory:%p\n",shm_addr);
        }
        
        sleep(1);
        printf("input string:\n");
            
        fgets(buff,BUFFER_SIZE-strlen(flag),stdin);
         
        strncpy(shm_addr+strlen(flag),buff,strlen(buff));
        strncpy(shm_addr,flag,strlen(flag));
         
        if(shmdt(shm_addr) < 0)
        {
             perror("parent:shmdt");
             exit(1);
        }
        else
            printf("parent: deattach shared memory\n");
            
        waitpid(pid,NULL,0);
        
        if(shmctl(shmid,IPC_RMID,NULL) == -1)
        {
            perror("shmctl:IPC_RMID");
            exit(1);
        }
        else
            printf("delete shared memory\n");
         
        printf("finished!\n");
    }

    return 0;
}
