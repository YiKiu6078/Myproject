#include <stdio.h> //客户端
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int clientfd2; //客户端socket

char *IP = "192.168.90.237"; //服务器的IP

short PORT = 6666; //服务器服务端口

typedef struct sockaddr meng;

//char user[50]; //设置支持的用户名长度

time_t nowtime;

sem_t sem1;

int line = 8; //打印消息时候的行数

int frame = 0; //是否在聊天框内 0:处在功能选择 1:处在聊天框

void progress_bar() //进度条
{

    // ****************************** 配置 ***************************
    // 最后100%时的输出形式
    const char *LastStr = "[--------------------] 100%";

    // 进度条标志，可以改用"*"或其它符号
    const char Progressicon = '-';

    // 进度每加5，进度条就会加一格，注意Step值要和LastStr中的"-"数量相匹配，两者相乘等于100
    const int Step = 5;

    // 总共需要多少进度标志，即LastStr中"-"的数量
    const int iconMaxNum = 20;

    // 每隔100ms打印一次，这里同时每隔200ms会让进度加1
    const int Printinterval = 20000;
    // ****************************************************************

    for (int i = 0; i <= 100; ++i)
    {
        // -------------- 打印进度条 --------------
        printf("\033[0;34m[\033[0m");
        int currentindex = i / Step;
        for (int j = 0; j < iconMaxNum; ++j)
        {
            if (j < currentindex)
            {
                printf("\033[0;34m%c\033[0m", Progressicon); // 打印进度条标志
            }
            else
            {
                printf(" "); // 未达进度则打印空格
            }
        }

        printf("\033[0;34m]\033[0m ");
        // ----------------------------------------

        // -------- 打印数字进度 ----------
        printf("\033[0;34m%3d%%\033[0m", i);
        fflush(stdout);
        // -------------------------------

        usleep(Printinterval);

        for (int j = 0; j < strlen(LastStr); ++j)
        {
            printf("\b"); // 回删字符，让数字和进度条原地变化
        }
        fflush(stdout);
    }
    printf("\n");
}

struct client //创建结构体
{
    int flag;          //功能标志位 -1:退出群聊 0:通知所有在线用户 1:私聊 2:群聊 3.发送文件 4.修改密码 5.管理员权限操作
    int root;          //权限标志位 -1:首次进入聊天室 0:普通用户 1:管理员 2;VIP用户
    int forbit;        //管理员权限 1:禁言 2:解除禁言 3:踢人
    char name[50];     //账号名
    char password[20]; //密码
    char msg[500];     //聊天信息
    char to_name[50];  //私聊对象
    struct client *next;
};
struct client Head;

void Clear_news() //清除输入框内容
{
    printf("\033[33;12H"); //将光标移动回到消息发送区
    printf("\033[K");      //清除发送框内容
    printf("\033[72C");
    printf("\033[0;34m|                 |\033[0m\n");
    printf("\033[33;12H \033[0;36m"); //将光标移动回到消息发送区
    printf("\033[36m");
}

void Clear_hint() //清除系统提示信息
{
    printf("\033[31;4H"); //将光标系统提示信息头位置
    printf("\033[K");      //清除系统提示信息
    printf("\033[80C");
    printf("\033[0;34m|                 |\033[0m\n");  
    printf("\033[33;12H \033[0;36m"); //将光标移动回到消息发送区
}

int print_msg(char *msg, int flag) //打印消息
{
    if (frame == 1)
    {
        if ((*msg == '\0') || (*msg == '\n') )
        {
            return 0;
        }
            
        char i_msg[500];
        printf("\033[s"); //保存光标位置
        fflush(stdout);

        if (line == 8)
            printf(" \033[8;4H"); //消息打印位置
        else if (line == 10)
            printf(" \033[10;4H"); //消息打印位置
        else if (line == 12)
            printf(" \033[12;4H"); //消息打印位置
        else if (line == 14)
            printf(" \033[14;4H"); //消息打印位置
        else if (line == 16)
            printf(" \033[16;4H"); //消息打印位置
        else if (line == 18)
            printf(" \033[18;4H"); //消息打印位置
        else if (line == 20)
            printf(" \033[20;4H"); //消息打印位置
        else if (line == 22)
            printf(" \033[22;4H"); //消息打印位置
        else if (line == 24)
            printf(" \033[24;4H"); //消息打印位置
        else if (line == 26)
            printf(" \033[26;4H"); //消息打印位置
        else if (line == 28)
            printf(" \033[28;4H"); //消息打印位置
        else if (line == 30)
            printf(" \033[30;4H"); //消息打印位置
        else if (line == 32)       //行数到达最后一行
        {
            if ((Head.root == 1) && (Head.flag == 2))
            {
                Root_frame(&Head);
            }
            else
            {
                Chat_frame(&Head);
            }

            printf(" \033[8;4H"); //消息打印位置
        }

        if (flag == 1) //打印收到的消息
        {
            printf("%s", msg);
            //printf("\033[0;34m |\033[0m");
        }
        else if (flag == 2) //打印发送的消息
        {
            sprintf(i_msg, "\033[0;36m%s\033[0;33m:我\033[0m\n", msg);
            printf("%*s", 99, i_msg);
        }
        //printf("%*s",80,msg);
        line = line + 2;
        printf(" \033[u"); //恢复光标位置
        fflush(stdout);
    }
    else if (frame == 0)
    {
        return 0;
    }
}

void Chat_frame(struct client *head) //打印聊天框
{
   
    system("clear");
    printf("\033[1;1H");
    fflush(stdout);
    line = 8;
    frame = 1;
    char name[50];
    char to_name[50];
    printf("\033[34m +===================================================================================================+\033[0m\n");
    printf("\033[34m |                                                                                                   |\033[0m\n");
    printf("\033[34m |\033[35m*********************************************\033[33m\033[1m飞飞聊天室\033[0;35m********************************************\033[34m|\033[0m\n");
    printf("\033[34m |                                                                                         \033[35m版本:1.0\033[34m  |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------------------------|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------|                 |\033[0m\n");
    printf("\033[34m |                                                                                 |\033[33m\033[1m用户:            \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[33m\033[1mw!:\033[0;36m文件发送     \033[34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------|                 |\033[0m\n");
    printf("\033[34m |\033[33m消息输入:\033[0;36m                                                                        \033[34m|                 |\033[0m\n");
    printf("\033[34m |                                                                                 |\033[35m输入\033[31mq!\033[0;35m退出聊天框\033[34m |\033[0m\n");
    printf("\033[34m +===================================================================================================+\033[0m\n");

    if (head->root == 1)
    {
        sprintf(name, "%s(管理员)\n", head->name);
    }
    else if (head->root == 2)
    {
        sprintf(name, "%s(VIP)\n", head->name);
    }
    else
    {
        sprintf(name, "%s\n", head->name);
    }

    if (head->flag == 2)
    {
        sprintf(to_name, "群聊\n");
    }
    else
    {
        sprintf(to_name, "%s\n", head->to_name);
    }
    printf("\033[6;40H");                          //将管标移到聊天对象打印位置
    printf("\033[33m\033[1m%s\033[0m\n", to_name); // 聊天对象

    printf(" \033[9;85H");                       //将管标移到用户名打印位置
    printf("\033[36m\033[1m%s\033[0m \n", name); // 用户名

    printf(" \033[33;12H \033[0;36m"); //将光标移动回到消息发送区
}

void Root_frame(struct client *head) //打印管理员群聊框
{
   // printf("\n");
    system("clear");
    printf("\033[1;1H");
    fflush(stdout);
    line = 8;
    frame = 1;
    char name[50];
    char to_name[50];
    printf("\033[34m +===================================================================================================+\033[0m\n");
    printf("\033[34m |                                                                                                   |\033[0m\n");
    printf("\033[34m |\033[35m*********************************************\033[33m\033[1m飞飞聊天室\033[0;35m********************************************\033[34m|\033[0m\n");
    printf("\033[34m |                                                                                         \033[35m版本:1.0\033[34m  |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------------------------|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------|                 |\033[0m\n");
    printf("\033[34m |                                                                                 |\033[33m\033[1m用户:            \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[33m\033[1m管理员权限：    \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[36m\033[1m1!:禁言         \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[36m\033[1m2!:解除禁言     \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[36m\033[1m3!:踢人        \033[0;34m |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[35m输入关键字      \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 | \033[35m进入对应权限    \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 | \033[33m\033[1mw!:\033[0;36m文件发送     \033[34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------|                 |\033[0m\n");
    printf("\033[34m |\033[33m消息输入:\033[0;36m                                                                        \033[34m|                 |\033[0m\n");
    printf("\033[34m |                                                                                 |\033[35m输入\033[31mq!\033[0;35m退出聊天框\033[34m |\033[0m\n");
    printf("\033[34m +===================================================================================================+\033[0m\n");

    sprintf(name, "%s(管理员)\n", head->name);

    sprintf(to_name, "群聊\n");

    printf("\033[6;40H");                          //将管标移到聊天对象打印位置
    printf("\033[33m\033[1m%s\033[0m\n", to_name); // 聊天对象

    printf(" \033[9;85H");                       //将管标移到用户名打印位置
    printf("\033[36m\033[1m%s\033[0m \n", name); // 用户名

    printf(" \033[33;12H \033[0;36m"); //将光标移动回到消息发送区
}

void Function_frame(struct client *head)  //打印功能选择界面
{
    system("clear");
    line = 8;
    frame = 0;
    char name[50];
    printf("\033[34m +===================================================================================================+\033[0m\n");
    printf("\033[34m |                                                                                                   |\033[0m\n");
    printf("\033[34m |\033[35m*********************************************\033[33m\033[1m飞飞聊天室\033[0;35m********************************************\033[34m|\033[0m\n");
    printf("\033[34m |                                                                                         \033[35m版本:1.0\033[34m  |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------------------------|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |\033[33m\033[1m用户:            \033[0;34m|\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                    \033[0;36m1:私聊功能\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                    \033[0;36m2:进入群聊\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                    \033[0;36m3:修改密码\033[0;34m                                   |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                   \033[0;31m0:退出聊天室\033[0;34m                                  |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n"); 
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |                                                                                 |                 |\033[0m\n");
    printf("\033[34m |---------------------------------------------------------------------------------|                 |\033[0m\n");
    printf("\033[34m |\033[33m消息输入:\033[0;36m                                                                        \033[34m|                 |\033[0m\n");
    printf("\033[34m |                                                                                 |\033[0;35m输入\033[31mq!\033[0;35m返回本界面\033[0;34m |\n");
    printf("\033[34m +===================================================================================================+\033[0m\n");
   
     if (head->root == 1)
    {
        sprintf(name, "%s(管理员)\n", head->name);
    }
    else if (head->root == 2)
    {
        sprintf(name, "%s(VIP)\n", head->name);
    }
    else
    {
        sprintf(name, "%s\n", head->name);
    }
    printf(" \033[9;85H");                       //将管标移到用户名打印位置
    printf("\033[36m\033[1m%s\033[0m \n", name); // 用户名

    printf(" \033[33;12H \033[0;36m"); //将光标移动回到消息发送区
}

void print_hint(char *msg) //打印系统提示消息
{
    Clear_hint(); //清除系统提示信息
    printf("\033[31;4H"); //将光标系统提示信息头位置
    printf("%s",msg);      //打印提示内容
    printf("\033[33;12H \033[0;36m"); //将光标移动回到消息发送区
}

int fileread(char *massage) //读取文件
{
    int flag = 0;
    int i;
    FILE *fp;
    char past[20];
    char filename[20];
    char buffer[500];
    char buffer1[500];
    char msg[100];

    sprintf(msg,"\033[0;33m请输入文件路径：\033[0m\n");
    print_hint(msg);//打印系统提示信息
    memset(msg, 0, sizeof(msg));
    scanf("%s", past);
    getchar();
    Clear_news(); //清除输入框内容

    sprintf(msg,"\033[0;33m请输入文件名：\033[0m\n");
    print_hint(msg);//打印系统提示信息
    memset(msg, 0, sizeof(msg));
    scanf("%s", filename);
    getchar();
    Clear_news(); //清除输入框内容

    strcat(past, filename);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        sprintf(msg,"\033[0;31m文件不存在!\033[35m(任意键继续，放弃请按1)\033[0m\n");
        print_hint(msg);//打印系统提示信息
        memset(msg, 0, sizeof(msg));
        scanf("%d",&flag);
        Clear_news(); //清除输入框内容
        if(flag == 1)
        {
            return 0;
        }
    }
    else
    {
        sprintf(msg,"\033[0;33m文件打开成功！\033[0m\n");
        print_hint(msg);//打印系统提示信息
        memset(msg, 0, sizeof(msg));
        fread(buffer, 1, sizeof(buffer), fp);
        sleep(1);
        //printf("\033[0;33m文件内容：\033[0;36m%s\033[0m\n", buffer);
    }
    if (strlen(buffer) == 1)
    {
        sprintf(msg,"\033[0;31m文件为空！\n是否往文件里写入信息.(写入请按1,其他任意键退出)\033[0m");
        print_hint(msg);//打印系统提示信息
        memset(msg, 0, sizeof(msg));
        scanf("%d", &i);
        getchar();
        Clear_news(); //清除输入框内容
        if (i == 1)
        {
            scanf("%s", buffer);
            getchar();
            fprintf(fp, "%s", buffer);
        }
        else
        {
            fclose(fp);
            return 0;
        }
    }
    if (strlen(buffer) != 0)
    {
        sprintf(buffer1, "%s\n%s", filename, buffer);
        //printf("buffer1:%s\n",buffer1);
        strcpy(massage, buffer1);
        fclose(fp);
        return 1;
    }
}

void filewrite(char *massage) //写文件
{
    int i = 0, len = 0, flag;
    FILE *fp;
    char filename[100] = "./gyf/";
    char filename1[100];
    char buffer[500];
    char msg[100];
    while (1)
    {
        if (massage[i] == '\n')
        {
            break;
        }
        len++;
        i++;
    }
    strncpy(filename1, massage, len);
    sprintf(msg,"\033[0;33m文件名：\033[0;36m%s\033[0m\n", filename1);
    print_hint(msg);//打印系统提示信息
    memset(msg, 0, sizeof(msg));
    sleep(1);
    strcat(filename, filename1);
    strcpy(buffer, &massage[len + 1]);
    //printf("\033[0;33m文件内容：\033[0;36m%s\033[0;36m", buffer);
    while (1)
    {
        flag = access(filename, 0);
        if (flag == -1)
        {
            break;
        }
        else if (flag == 0)
        {
            len = strlen(filename);
            while (filename[len - 1] != '.')
            {
                len--;
            }
            char post[10];
            strcpy(post, &filename[len - 1]);
            strcpy(&filename[len - 1], "\0");
            strcat(filename, "(1)");
            strcat(filename, post);
        }
    }
    fp = fopen(filename, "w+");
    fprintf(fp, "%s", buffer);
    fclose(fp);
    memset(filename, 0, sizeof(filename));
    memset(filename1, 0, sizeof(filename1));
    memset(buffer, 0, sizeof(buffer));

    Clear_hint();//清除系统提示信息
}

int search(struct client *head) //登录
{
    void log_in();  //声明
    int flag = -1;  //密码正确错误标志位     0:密码错误 1:密码正确
    int flag1 = -1; //该账号是否登录标志位   0:未登录 1:已登录
    int flag2 = -1; //该用户是否存在标志位   0:不存在 1:存在

    printf("\33[0;34m请输入用户名：\33[0m\n");
    scanf("%s", head->name);
    getchar();
    write(clientfd2, head->name, strlen(head->name));
    int readflag = read(clientfd2, &flag2, sizeof(flag2)); //读取用户是否存在的标识符
    if (flag2 > 0)
    {
        read(clientfd2, &flag1, sizeof(flag1)); //读取用户是否已经被登录的标识符
        if (flag1 == 0)                         //0为未被登录，即可进行登录
        {
            if (head->root == 1)
            {
                write(clientfd2, &head->root, sizeof(head->root));
                head->root = -1;
                read(clientfd2, &head->root, sizeof(head->root));
                if (head->root == 0)
                {
                    int key = 0;
                    printf("\033[0;31m该用户不是管理员！\033[0m\n");
                    printf("\033[0;33m是否继续以管理员身份登录？(任意键继续，按1返回初始界面！)\033[0m\n");
                    scanf("%d", &key);
                    if (key == 1)
                    {
                        log_in(head); //返回初始界面
                    }
                    else
                    {
                        search(head);
                    }
                }
            }
            else if (head->root == 0)
            {
                write(clientfd2, &head->root, sizeof(head->root));
            }

            printf("\33[0;34m请输入密码：\33[0m\n");
            scanf("%s", head->password);
            getchar();
            write(clientfd2, head->password, 20);
            read(clientfd2, &flag, sizeof(flag));
            if (flag)
            {
                printf("\033[0;34m正在登录中\033[0m");
                int vip;
                read(clientfd2, &vip, sizeof(vip)); //判断该用户是否为VIP
                if (vip == 1)
                {
                    head->root = 2;
                }
                progress_bar();

                return 1;
            }
            else if (flag == 0)
            {
                printf("\33[0;31m用户名或密码输入错误！\033[0m\n");
                printf("\33[0;31m请重新输入！\033[0m\n");
                search(head);
            }
        }
        else if (flag1 != 0)
        {
            printf("\33[0;31m该用户名已在其他客户端登录！\033[0m\n");
            printf("\33[0;31m请重新输入！\033[0m\n");
            search(head);
        }
    }
    else if (flag2 == 0)
    {
        printf("\33[0;31m该用户不存在!\33[0m\n");
        printf("\33[0;31m请重新输入！\033[0m\n");
        search(head);
    }
}

int sign_in(struct client *head) //用户帐号注册
{
    //获取注册用户名和密码
    while (1)
    {
        int flag = -1;
        // printf("flag:%d\n", flag);
        printf("\33[0;34m请输入用户名:\33[0m\n");
        scanf("%s", head->name);
        getchar();
        write(clientfd2, head->name, strlen(head->name));
        int readflag = read(clientfd2, &flag, sizeof(flag));

        if (readflag < 0)
        {
            break;
        }

        if (flag == 0)
        {
            printf("\33[0;34m请输入用户密码:\33[0m\n");
            scanf("%s", head->password);
            getchar();
            if (head->name[0] != '\0')
            {
                int ret = write(clientfd2, head->password, strlen(head->password));
                if (ret > 0)
                {
                    printf("\033[0;34m注册中\033[0m");
                    progress_bar();
                    printf("\033[0;34m注册成功!\033[0m\n");
                    printf("\033[0;36m用户名:%s\033[0m\n", head->name);
                    printf("\033[0;36m用户密码:%s\033[0m\n\n", head->password);
                    break;
                }
            }
        }
        else if (flag > 0)
        {
            printf("\033[0;31m用户名已被占用！\n请重新输入！\n\033[0m");
        }
    }
}

void n_init() //初始化
{
    clientfd2 = socket(PF_INET, SOCK_STREAM, 0); //创建套接字
    struct sockaddr_in addr;                     //将套接字存在sockaddr_in结构体中
    addr.sin_family = PF_INET;                   //地址族
    addr.sin_port = htons(PORT);                 //端口号 可随意设置，不过不可超过规定的范围
    addr.sin_addr.s_addr = inet_addr(IP);        //inet_addr()函数将点分十进制的字符串转换为32位的网络字节顺序的ip信息

    //发起连接
    if (connect(clientfd2, (meng *)&addr, sizeof(addr)) == -1)
    {
        perror("\033[0;31m无法连接到服务器\033[0m");
        exit(-1);
    }
    printf("\033[0;33m客户端启动成功\n\033[0m");
}

void *recv_thread(void *p) //用于接收聊天信息
{
    char flag[20] = {};
    strcpy(flag, "flag==3");
    char buf[500] = {};
    char msg[100];
    while (1)
    { 
        char *str = buf;
        if (recv(clientfd2, buf, sizeof(buf), 0) <= 0)
        {
            break;
        }

        if (strcmp(buf, flag) == 0) //进行文件接收准备
        {
            recv(clientfd2, buf, 500, 0);
            while (*str == '\0')
            {
                str++;
            }
            printf("\033[s"); //保存光标位置
            fflush(stdout);

            //printf("\033[?25l");  //隐藏光标
            printf("\033[31;4H"); //将光标移动到系统提示信息头位置  
            printf("\033[0;33m文件接收中\033[0m");
            progress_bar();
            memset(msg, 0, sizeof(msg));
            //printf("\033[33;12H \033[0;36m"); //将光标移动回到消息发送区
            //print_msg(buf, 3); //打印接收文件的消息
            sprintf(msg, "\033[0;35m文件接收成功！\033[0;36m");
            print_msg(msg,1);//打印信息
            sleep(1);
            memset(msg, 0, sizeof(msg));
            filewrite(str);  //写文件
           
            //printf(" \033[u"); //恢复光标位置
            fflush(stdout);
            //Clear_news(); //清除输入框内容
            printf("\033[36m");
            //printf("1\n");
           // Clear_news(); //清除输入框内容
           printf("\033[?25h"); //显示光标
            
                   
           // printf("\033[12C \033[1A");
            
        }
        else
        {
            print_msg(buf, 1); //打印接收的消息
        }
        memset(buf, 0, sizeof(buf));
    }
}

void transfer_file(struct client *head,int temp) //文件传输
{
    char msg[100];
    if(temp == 1)  //该用户处在群聊
    {
        sprintf(msg,"\033[0;33m请输入发送对象 ：\033[0m\n");
        print_hint(msg);//打印系统提示信息
        memset(msg, 0, sizeof(msg));
        scanf("%s", head->to_name);
        getchar();
        Clear_news(); //清除输入框内容
    }
    
    while (1)
    {
        int y;
        int i = fileread(head->msg);
        if(i == 0)
        {
            break;
        }
        else if (i == 1)
        {
            send(clientfd2, head, sizeof(struct client), 0);
            printf("\033[?25l");  //隐藏光标
            printf("\033[31;4H"); //将光标系统提示信息头位置
            printf("\033[0;33m文件发送中\033[0m");
            progress_bar();
            memset(msg, 0, sizeof(msg));
            printf("\033[33;12H \033[0;36m"); //将光标移动回到消息发送区
            printf("\033[?25h"); //显示光标
            sprintf(msg,"\033[0;33m文件发送成功！\033[0;35m(按任意键继续，退出请按1)\033[0;36m\n");
            print_hint(msg);//打印系统提示信息
            memset(msg, 0, sizeof(msg));
            scanf("%d", &y);
            getchar();
            Clear_news(); //清除输入框内容
            //printf("1\n");
           // Clear_news(); //清除输入框内容
            printf("\033[36m");
        }
        else
        {
            sprintf(msg,"\033[0;31m文件为空，无法传送！\033[0m\n");
            print_hint(msg);//打印系统提示信息
            memset(msg, 0, sizeof(msg));
        }
        
        if (y == 1)
        {
            break;
        }
    }
}

void group_chat(struct client *head) //私聊、群聊
{
    void Chat_choose(); //声明
    
    if (1 == head->flag) //私聊
    {
        char msg[100];
        sprintf(msg,"\033[0;35m请输入私聊对象：\033[0m");
        print_hint(msg);//打印系统提示信息
        memset(msg, 0, sizeof(msg)); 
        scanf("%s", head->to_name);
        getchar();
        Clear_news(); //清除输入框内容
        //printf("\033[0;35m已进入与%s的私聊界面！\033[0m\n", head->to_name);
    }
    else if (2 == head->flag) //群聊
    {
        int temp = head->root; //记录用户root值
        head->root = -1;       //让服务器将该用户加入到群成员
        send(clientfd2, head, sizeof(struct client), 0);
        head->root = temp;
        //printf("\033[0;35m欢迎进入群聊！\033[0m\n");
    }

    Head = *head;
    //打印聊天框
    if ((head->root == 1) && (head->flag == 2))
    {
        Root_frame(head);
    }
    else
    {
        Chat_frame(head);
    }

    //消息输入
    while (1)
    {
        char buf[500] = {};
        //printf("\033[0;36m");
        scanf("%s", head->msg);
        getchar();

        //判断关键字
        if (strcmp(head->msg, "q!") == 0) //群出聊天
        {
            if (head->flag == 2)
            {
                head->flag = -1;
                send(clientfd2, head, sizeof(struct client), 0); //退出群聊
            }
            Chat_choose(head);
        }

        if (strcmp(head->msg, "w!") == 0) //发送文件
        {
            Clear_news(); //清除输入框内容
            if(head->flag == 1)
            {
                head->flag = 3;
                transfer_file(head,0); //文件传输
                head->flag = 1;
            }
            else if(head->flag == 2)
            {
                head->flag = 3;
                transfer_file(head,1); //文件传输
                head->flag = 2;
            }
            Clear_hint();//清除系统提示信息
            continue;  //结束本次循环，进入下次循环
        }

        if (strcmp(head->msg, "1!") == 0) //禁言
        {
            Clear_news(); //清除输入框内容
            if ((head->root == 1) && (head->flag == 2))
            {
                head->flag = 5;
                manage(head, 1);
                head->flag = 2;
                continue;
            }
        }
        if (strcmp(head->msg, "2!") == 0) //解除禁言
        {
            Clear_news(); //清除输入框内容
            if ((head->root == 1) && (head->flag == 2))
            {
                head->flag = 5;
                manage(head, 2);
                head->flag = 2;
                continue;
            }
        }
        if (strcmp(head->msg, "3!") == 0) //踢出群聊
        {
            Clear_news(); //清除输入框内容
            if ((head->root == 1) && (head->flag == 2))
            {
                head->flag = 5;
                manage(head, 3);
                head->flag = 2;
                continue;
            }
        }

        
        Clear_news(); //清除聊天框内容

        //靠左边打印发送的消息
        /*sprintf(buf, "\033[0;33m\033[1m我：\033[0;36m%s\033[0m\n", head->msg);
          print_msg(buf, 1); //靠左边打印发送的消息*/

        //靠右边打印发送的消息
        print_msg(head->msg, 2); //靠右边打印发送的消息

        if (head->flag == 2)
        {
            if (head->root == 1)
            {
                sprintf(buf, "\033[0;33m(管理员)\033[0;34m%s\033[0;36m：%s\033[0m\n", head->name, head->msg);
            }
            else
            {
                sprintf(buf, "\033[0;34m%s：\033[0;36m%s\033[0m\n", head->name, head->msg);
            }
            strcpy(head->msg, buf);
            memset(buf, 0, sizeof(buf));
        }

        send(clientfd2, head, sizeof(struct client), 0);
    }
}

void alter(struct client *head) //修改密码
{
    void Chat_choose();
    int flag = -1;                                   //用来判断密码输入是否正确
    send(clientfd2, head, sizeof(struct client), 0); //让服务器进入修改密码等待
    char pw[20];
    char pw1[20];
    char msg[100];
    while (1)
    {
        sprintf(msg,"\033[0;33m请输入旧密码：\033[0m\n");
        print_hint(msg);//打印系统提示信息
        memset(msg, 0, sizeof(msg));
        scanf("%s", pw);
        Clear_news(); //清除输入框内容
        if (strcmp(head->password, pw) == 0)
        {
            sprintf(msg,"\033[0;33m请输入新密码：\033[0m\n");
            print_hint(msg);//打印系统提示信息
            memset(msg, 0, sizeof(msg));
            memset(pw, 0, 20);
            scanf("%s",pw);
            getchar();
            Clear_news(); //清除输入框内容

            sprintf(msg,"\033[0;33m请确认密码：\033[0m\n");
            print_hint(msg);//打印系统提示信息
            memset(msg, 0, sizeof(msg));
            memset(pw1, 0, 20);
            scanf("%s", pw1);
            getchar();
            Clear_news(); //清除输入框内容

            if (strcmp(pw, pw1) == 0)
            {
                strcmp(head->password, pw);
                int ret = write(clientfd2, head->password, strlen(head->password));
                if (ret > 0)
                {
                    printf("\033[31;4H"); //将光标移动到系统提示信息头位置  
            printf("\033[0;33m服务器修改中\033[0m");
            progress_bar();
            memset(msg, 0, sizeof(msg));
                  
                    sprintf(msg,"\033[0;35m密码修改成功！\033[0m\n");
                    print_hint(msg);//打印系统提示信息
                    memset(msg, 0, sizeof(msg));
                    sleep(1);
                    Clear_hint();
                    break;
                }
                else
                {
                    sprintf(msg,"\033[0;31m密码修改失败，请重新输入!\033[0m\n");
                    print_hint(msg);//打印系统提示信息
                    memset(msg, 0, sizeof(msg));
                    sleep(1);
                }
            }
            else
            {
                sprintf(msg,"\033[0;31m;两次密码输入有误！请重新输入！\033[0m\n");
                print_hint(msg);//打印系统提示信息
                memset(msg, 0, sizeof(msg));
                sleep(1);
            }
        }
        else
        {
            int temp = 0;
            sprintf(msg,"\033[0;31m密码输入错误!是否继续输入\033[0;35m(任意键继续，放弃请按1)\033[0m\n");
            print_hint(msg);//打印系统提示信息
            memset(msg, 0, sizeof(msg));
            scanf("%d", &temp);
            Clear_news(); //清除输入框内容
            if (temp == 1)
            {
                Chat_choose(head);
            }
        }
    }
}

void manage(struct client *head, int flag) //管理员权限
{
    Clear_news(); //清除输入框内容
    char msg[100];
    int temp = 0;
    // sprintf(msg,"\033[0;33m请输入禁言用户：\033[0m\n");
    //         print_hint(msg);//打印系统提示信息
    while (1)
    {
        if (1 == flag)
        {
            head->forbit = 1;
            sprintf(msg,"\033[0;33m请输入禁言用户：\033[0m\n");
            print_hint(msg);//打印系统提示信息
            memset(msg, 0, sizeof(msg));
            scanf("%s", head->to_name);
            getchar();
            Clear_news(); //清除输入框内容
            send(clientfd2, head, sizeof(struct client), 0);
            usleep(100);
        }
        else if (2 == flag)
        {
            head->forbit = 2;
            sprintf(msg,"\033[0;33m请输入解禁用户：\033[0m\n");
            print_hint(msg); //打印系统提示信息
            memset(msg, 0, sizeof(msg));
            scanf("%s", head->to_name);
            getchar();
            Clear_news(); //清除输入框内容
            send(clientfd2, head, sizeof(struct client), 0);
            usleep(100);
        }
        else if (3 == flag)
        {
            head->forbit = 3;
            sprintf(msg,"\033[0;33m请输入被踢用户：\033[0m\n");
            print_hint(msg);//打印系统提示信息
            memset(msg, 0, sizeof(msg));
            scanf("%s", head->to_name);
            getchar();
            Clear_news(); //清除输入框内容
            send(clientfd2, head, sizeof(struct client), 0);

        }
        memset(msg, 0, sizeof(msg));
        sprintf(msg,"\033[0;33m\033[1m是否继续：\033[0;33m(任意键继续，结束请按1)\033[0m \n");
        print_hint(msg);//打印系统提示信息
        memset(msg, 0, sizeof(msg));
        scanf("%d", &temp);
        getchar();
        Clear_news(); //清除输入框内容
        if(1 == temp)
        {
            Clear_hint();//清除系统提示信息
            break;
        }
        
    }
}

void Chat_choose(struct client *head) //聊天模式选择
{

    int count = 0;
    char msg[100];
    frame = 0;
    Function_frame(head);//打印功能选择框
    sprintf(msg,"\033[0;34m请输入功能选择项：\033[0m \n");
    print_hint(msg);//打印系统提示信息
    memset(msg, 0, sizeof(msg));
    while (1)
    {
        scanf("%d", &count);
        getchar();
        Clear_news(); //清除输入框内容
        printf("\n");
        switch (count)
        {
        case 1:
            Clear_hint();//清除系统提示信息
            head->flag = 1;
            group_chat(head); //私聊功能

        case 2:
            Clear_hint();//清除系统提示信息
            head->flag = 2;
            group_chat(head); //群聊功能
            break;
        case 3:
            Clear_hint();//清除系统提示信息
            head->flag = 4;
            alter(head); //修改密码
            break;
        case 0:
            printf(msg,"\033[0;33m退出成功！欢迎下次使用！\033[0m\n");
            print_hint(msg);//打印系统提示信息
            memset(msg, 0, sizeof(msg));
            close(clientfd2);
            printf("\033[35,0H");
            exit(-1);
            break;
        default:
            printf("\033[0;31m选择有误！请重新输入！\033[0m\n");
            print_hint(msg);//打印系统提示信息
            memset(msg, 0, sizeof(msg));
            break;
        }
    }
}

void log_in(struct client *head) //登录&注册
{
    int select;
    system("clear");
    printf("\033[0;34m+================================================================+\033[0m\n");
    printf("\033[0;34m|                                                                |\033[0m\n");
    printf("\033[0;34m|***********************\033[0;33m欢迎来到飞飞聊天室\033[0;34m***********************|\033[0m\n");
    printf("\033[0;34m|                                                    　 版本:1.0 |\033[0m\n");
    printf("\033[0;34m|----------------------------------------------------------------|\033[0m\n");
    printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m|                         \033[0;36m1.用户登录        　                   \033[0;34m|\033[0m\n");
    printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m|                         \033[0;36m2.帐号注册                             \033[0;34m|\033[0m\n");
    printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m|                         \033[0;33m3.管理员登录                           \033[0;34m|\033[0m\n");
    printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m|                        \033[0;31m 0:退出聊天室                           \033[0;34m|\033[0m\n");
    printf("\033[0;34m|                                        　                      |\033[0m\n");
    printf("\033[0;34m+================================================================+\033[0m\n");
    printf("\n");
    while (1)
    {
        printf("\033[0;34m请选择:\033[0m\n");
        scanf("%d", &select);
        getchar();

        if (1 == select)
        {
            write(clientfd2, &select, sizeof(select));
            head->root = 0; //普通用户登录
            search(head);
            break;
        }
        else if (2 == select)
        {
            write(clientfd2, &select, sizeof(select));
            sign_in(head);
        }
        else if (3 == select)
        {
            select = 1;
            write(clientfd2, &select, sizeof(select));
            head->root = 1; //管理员登录
            search(head);
            break;
        }
        else if (0 == select)
        {
            printf("\033[0;33m退出成功！\033[0m\n");
            printf("\033[0;33m欢迎下次使用！\033[0m\n");
            exit(-1);
            break;
        }
        else
        {
            printf("\033[0;31m选择错误！请重新输入！\033[0m\n");
        }
    }
}

int main()
{
    struct client head;
    n_init();
    log_in(&head); //进入登录注册界面

    //创建一个线程用于数据的接收
    pthread_t id;
    void *recv_thread(void *);
    int ret1 = pthread_create(&id, 0, recv_thread, 0);
    if (ret1 != 0)
    {
        perror("pthread_create1:");
        exit(1);
    }

    //让服务器告诉所有在线用户，该用户进入聊天室
    if (head.root == 1)
    {
        sprintf(head.msg, "\033[0;33m%s\033[0;35m(管理员)\033[0;33m进入了聊天室!\033[0m\n", head.name);
    }
    else
    {
        sprintf(head.msg, "\033[0;33m%s进入了聊天室!\033[0m\n", head.name);
    }
    head.flag = 0;
    send(clientfd2, &head, sizeof(struct client), 0);
    memset(head.msg, 0, sizeof(head.msg));

    Chat_choose(&head); //进入聊天室功能界面

    close(clientfd2);
    return 0;
}


