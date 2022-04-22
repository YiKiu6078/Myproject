#include "address_list.h"

void read_file(Hlink head)
{
    int fp;
    int ret;
   
    //打开文件  调用open函数
    fp = open("textbook", O_RDWR | O_CREAT, 0644);
  
    if( fp < 0)
    {
        perror("open error!\n");
        exit(1);
    }
   
    while(1)
    {
        Hlink new_node = (Hlink)malloc(sizeof(Node));

        ret = read(fp,new_node,sizeof(Node));

        if(ret == 0)
        {
            break;
        }    

        if(ret = -2)
        {
            perror("error");
        }

        new_node->next = head->next;
        head->next = new_node;
    }
    

    close(fp);


}
