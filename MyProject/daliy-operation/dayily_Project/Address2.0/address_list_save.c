#include "address_list.h"
#include <stdlib.h>

//保存通讯录到文件
//用系统调用函数

void address_list_save(Hlink head)
{   
    int fd;
    Hlink p = NULL;
    p = head->next;

   //打开文件  调用open函数
   fd = open("textbook", O_RDWR | O_CREAT, 0644);

   if( fd < 0)
   {
       perror("open error!\n");
       exit(1);
   }

   if(p == NULL)
   {
       printf("通讯录空空如也！\n");
   } 

   while(p != NULL)
   {     
       write(fd, p ,sizeof(Node));  
          
       p = p->next;
   }

   printf("保存成功！\n");

   
   close(fd);


}














