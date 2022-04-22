#include <stdio.h> //服务器
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <sqlite3.h>
#include <string.h>
#include <unistd.h>

int serverfd; //服务器socket

int clientfd[100]; //客户端的socketfd,100个元素，clientfd[0]~clientfd[99]

int size = 50; //用来控制进入聊天室的人数为50以内

char *IP = "192.168.90.237"; //主机ip地址

short PORT = 6666; //端口号

typedef struct sockaddr meng;

time_t nowtime;

struct client //创建结构体
{
    int flag;          //功能标志位  -1:退出群聊   0:通知所有在线用户   1:私聊   2:群聊   3.发送文件   4.修改密码
    int root;          //权限标志位  -1:首次进入聊天室   0:普通用户   1:管理员  2:VIP用户
    int forbit;        //管理员权限   1:禁言   2:解除禁言   3:踢人
    char name[50];     //账号名
    char password[20]; //密码
    char msg[500];     //聊天信息
    char to_name[50];  //操作对象
    struct client *next;
};

struct Forbit //存放被禁言人员
{
    char name[50];
    struct Forbit *next;
};

struct Root //存放管理员名单
{
    char root[50]; //管理员用户
    struct Root *next;
};

struct VIP //存放vip用户名单
{
    char name[50]; //管理员用户
    struct VIP *next;
};

struct user //用来存放已登录用户
{
    int c_fd;
    char name[50];
    struct user *next;
};

struct Group //存放群内成员
{
    char name[50]; //群内成员用户
    struct Group *next;
};

struct i_fd
{
    int i;
    int c_fd;
};

struct Node //存放已注册用户
{
    char name[50];
    char password[20];
    struct Node *next;
};

int personalflag[500] = {-1};
sem_t sem[500];
sem_t sem1[500];
struct user *h;  //已登录用户头节点
struct Node *h1; //已注册用户头节点
pthread_t pti1[500];
struct Forbit *F_head;            //禁言人员头节点
struct Root *r_head;              //管理员人员头节点
struct Group *G_head;             //群内成员头结点
struct VIP *V_head;               //VIP用户头结点
void insert_fp(struct Root *root) //把文件里的存到链表里，每次打开时初始化使用
{
    int cnt;
    FILE *fp;
    FILE *dp;
    dp = fopen("./R_num.txt", "r");
    fscanf(dp, "%d", &cnt);
    fclose(dp);
    fp = fopen("./root.txt", "a+");

    while (cnt != 0)
    {
        struct Root *newcilent = (struct Root *)malloc(sizeof(struct Root)); //申请空间
        if (NULL == newcilent)
        {
            return;
        }
        fscanf(fp, "%s \n", newcilent->root);
        newcilent->next = NULL;
        root->next = newcilent;
        root = root->next;
        cnt--;
    }
    fclose(fp);
}

int r_init(struct Root **root) //创建管理员用户链表头节点
{
    struct Root *newcilent = (struct Root *)malloc(sizeof(struct Root));
    if (NULL == newcilent)
    {
        return -1;
    }

    newcilent->next = NULL;
    *root = newcilent;
    int cnt = 0; //计数储存文件初始化
    FILE *dp;
    char ch;
    dp = fopen("./R_num.txt", "a"); //如果没有，则创建一个，而且不会覆盖原有的数据
    fclose(dp);
    dp = fopen("./R_num.txt", "r"); //关闭之后，再以只读模式打开
    ch = fgetc(dp);
    fclose(dp);

    if (ch == EOF) //如果ch=EOF，则证明文件为空，初始化应该存个零进去
    {
        dp = fopen("./R_num.txt", "w"); //写会覆盖
        fprintf(dp, "%d", cnt);
        fclose(dp);
    }
    else if (ch != EOF) //如果不为空，则把之前存的文件放进链表
    {

        insert_fp(*root);
    }
}

void V_insert_fp(struct VIP *vip) //把文件里的存到链表里，每次打开时初始化使用
{
    int cnt;
    FILE *fp;
    FILE *dp;
    dp = fopen("./V_num.txt", "r");
    fscanf(dp, "%d", &cnt);
    fclose(dp);
    fp = fopen("./VIP.txt", "a+");

    while (cnt != 0)
    {
        struct VIP *newcilent = (struct VIP *)malloc(sizeof(struct VIP)); //申请空间
        if (NULL == newcilent)
        {
            return;
        }
        fscanf(fp, "%s \n", newcilent->name);
        newcilent->next = NULL;
        vip->next = newcilent;
        vip = vip->next;
        cnt--;
    }
    fclose(fp);
}

int V_init(struct VIP **vip) //创建VIP用户链表头节点
{
    struct VIP *newcilent = (struct VIP *)malloc(sizeof(struct VIP));
    if (NULL == newcilent)
    {
        return -1;
    }

    newcilent->next = NULL;
    *vip = newcilent;
    int cnt = 0; //计数储存文件初始化
    FILE *dp;
    char ch;
    dp = fopen("./V_num.txt", "a"); //如果没有，则创建一个，而且不会覆盖原有的数据
    fclose(dp);
    dp = fopen("./V_num.txt", "r"); //关闭之后，再以只读模式打开
    ch = fgetc(dp);
    fclose(dp);

    if (ch == EOF) //如果ch=EOF，则证明文件为空，初始化应该存个零进去
    {
        dp = fopen("./V_num.txt", "w"); //写会覆盖
        fprintf(dp, "%d", cnt);
        fclose(dp);
    }
    else if (ch != EOF) //如果不为空，则把之前存的文件放进链表
    {

        V_insert_fp(*vip);
    }
}

int init(struct user **head) //创建已登录用户链表头节点
{
    struct user *newnode = (struct user *)malloc(sizeof(struct user));
    if (NULL == newnode)
    {
        return -1;
    }
    newnode->c_fd = 0;
    newnode->name[0] = 0;
    newnode->next = NULL;
    *head = newnode;
}

int init1(struct Node **head) //创建已注册用户链表头节点
{
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    if (NULL == newnode)
    {
        return -1;
    }
    newnode->name[0] = 0;
    newnode->password[0] = 0;
    newnode->next = NULL;
    *head = newnode;
}

int F_init(struct Forbit **head) //创建被禁言人员链表头节点
{
    struct Forbit *newnode = (struct Forbit *)malloc(sizeof(struct Forbit));
    if (NULL == newnode)
    {
        return -1;
    }
    newnode->name[0] = 0;
    newnode->next = NULL;
    *head = newnode;
}

int G_init(struct Group **head) //创建群内成员链表头节点
{
    struct Group *newnode = (struct Group *)malloc(sizeof(struct Group));
    if (NULL == newnode)
    {
        return -1;
    }
    newnode->name[0] = 0;
    newnode->next = NULL;
    *head = newnode;
}

int insert_forbit(struct Forbit *head, char *name) //添加被禁言人员
{
    struct Forbit *newnode = (struct Forbit *)malloc(sizeof(struct Forbit));
    if (NULL == newnode)
    {
        return -1;
    }
    strcpy(newnode->name, name);
    newnode->next = NULL;
    while (head->next != NULL)
    {
        if (strcmp(head->next->name, name) == 0)
        {
            return 1;
        }
        head = head->next;
    }
    head->next = newnode;
    return 0;
}

int insert_group(struct Group *head, char *name) //添加群内成员
{
    struct Group *newnode = (struct Group *)malloc(sizeof(struct Group));
    if (NULL == newnode)
    {
        return -1;
    }
    strcpy(newnode->name, name);
    newnode->next = NULL;
    while (head->next != NULL)
    {
        if (strcmp(head->next->name, name) == 0)
        {
            return 1;
        }
        head = head->next;
    }
    head->next = newnode;
    return 0;
}

int delete_forbit(struct Forbit *head, char *name) //移除被禁言人员
{

    int count = 0;
    while (head->next != NULL)
    {
        if (strcmp(head->next->name, name) == 0)
        {
            struct Forbit *ptr = head->next;
            head->next = ptr->next;
            free(ptr);
            count++;
        }
        else
        {
            head = head->next;
        }
    }
    if (count == 0)
    {
        return 1; //该用户未被禁言
    }
    return 0;
}

int delete_group(struct Group *head, char *name) //移除群内成员
{

    int count = 0;
    while (head->next != NULL)
    {
        if (strcmp(head->next->name, name) == 0)
        {
            struct Group *ptr = head->next;
            head->next = ptr->next;
            free(ptr);
            count++;
        }
        else
        {
            head = head->next;
        }
    }
    if (count == 0)
    {
        return 1; //该用户不在群内
    }
    return 0;
}

struct user *insert_tail(struct user *head, int c_fd, char *name) //添加已登录用户
{
    struct user *newnode = (struct user *)malloc(sizeof(struct user));
    if (NULL == newnode)
    {
        return NULL;
    }
    newnode->c_fd = c_fd;
    strcpy(newnode->name, name);
    newnode->next = NULL;
    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = newnode;
    return newnode;
}

struct Node *insert(struct Node *head, char *name, char *password) //添加注册用户
{
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    if (NULL == newnode)
    {
        return NULL;
    }
    strcpy(newnode->name, name);
    strcpy(newnode->password, password);
    newnode->next = NULL;
    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = newnode;
    return newnode;
}

int searchuser(struct user *head, char *name) //搜索存在用户名是否存在,存在返回线程号
{
    while (head->next != NULL)
    {
        if (strcmp(head->next->name, name) == 0)
        {
            return head->next->c_fd;
        }
        else
        {
            head = head->next;
        }
    }
    //int flag = 0;
    int flag = search1(name);
    return flag;
}

void Init() //初始化
{
    serverfd = socket(PF_INET, SOCK_STREAM, 0);
    printf("\033[0;34m创建socket成功！\033[0m\n");
    if (serverfd == -1)
    {
        perror("\033[0;31m创建socket失败\033[0m");
        exit(-1);
    }

    //为套接字设置ip协议 设置端口号  并自动获取本机ip转化为网络ip
    struct sockaddr_in addr;              //存储套接字的信息
    addr.sin_family = PF_INET;            //地址族
    addr.sin_port = htons(PORT);          //设置server端端口号，你可以随便设置,当sin_port = 0时，系统随机选择一个未被使用的端口号
    addr.sin_addr.s_addr = inet_addr(IP); //把127.0.0.1改为自己的server端的ip地址,当sin_addr = INADDR_ANY时，表示从本机的任一网卡接收数据

    //绑定套接字
    if (bind(serverfd, (meng *)&addr, sizeof(addr)) == -1)
    {
        perror("\033[0;31m绑定失败\033[0m");
        exit(-1);
    }
    //printf("\033[0;34m绑定套接字成功！\033[0m\n");

    if (listen(serverfd, 100) == -1)
    { //监听最大连接数

        perror("\033[0;31m设置监听失败!\033[0m");
        exit(-1);
    }
    //printf("\033[0;34m监听成功！\033[0m\n");
}

void insertdb(struct Node *head)
{
    char sql[500] = "\0";
    sprintf(sql, "insert into user (name,password) values('%s','%s');", head->name, head->password); //插入，修改，删除都可以用这条语句
    carryout(sql);
}

void search(char *n, char *pw) //搜索密码
{
    struct Node *head = h1;
    while (head->next != NULL)
    {
        head = head->next;
        if (strcmp(n, head->name) == 0)
        {
            strcpy(pw, head->password);
        }
    }
}

int search1(char *n) //搜索用户名是否存在
{
    int count = 0;
    struct Node *head = h1;
    while (head->next != NULL)
    {
        head = head->next;
        if (strcmp(n, head->name) == 0)
        {
            count++;
            //printf("count:%d\n", count);
        }
    }
    return count;
}

int search2(char *n) //搜索是否已经登录
{
    //printf("搜索是否已经登录\n");
    int flag = 0;
    struct user *head = h;
    while (head->next != NULL)
    {
        head = head->next;
        //printf("head.name:%s\n", head->name);
        if (strcmp(n, head->name) == 0)
        {
            //printf("已经登录\n");
            flag = 1;
            //printf("搜索完成\n");
            return 1;
        }
    }
    if (flag == 0)
    {
        return 0;
    }
    //printf("搜索完成\n");
}

int seek_Group(char *n) //搜索该成员是否为群成员
{
    struct Group *head = G_head;
    while (head->next != NULL)
    {
        head = head->next;
        if (strcmp(n, head->name) == 0) //该用户为群成员
        {
            return 1;
        }
    }
    return 0; //该用户不是群成员
}

int seek_VIP(char *n) //搜索该成员是否为VIP用户
{
    struct VIP *head = V_head;
    while (head->next != NULL)
    {
        head = head->next;
        if (strcmp(n, head->name) == 0) //该用户为VIP用户
        {
            return 1;
        }
    }
    return 0; //该用户不是VIP用户
}

int seek_forbit(char *n) //搜索该成员是否被禁言
{
    struct Forbit *head = F_head;
    while (head->next != NULL)
    {
        head = head->next;
        if (strcmp(n, head->name) == 0) //该用户被禁言
        {
            return 1;
        }
    }
    return 0; //该用户未被禁言
}

void update_pw(char *name, char *pw)
{
    struct Node *head = h1;
    while (head->next != NULL)
    {
        head = head->next;
        if (strcmp(name, head->name) == 0)
        {
            strcpy(head->password, pw);
        }
    }
}

void display(struct user *head) //显示在线用户
{
    while (head->next != NULL)
    {
        //printf("c_fd=%d\nname=%s\n", head->next->c_fd, head->next->name);
        head = head->next;
    }
}

void createtable()
{
    sqlite3 *db = NULL;
    int ret = sqlite3_open("info.db", &db); //打开数据库
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_open:");
        exit(1);
    }
    char *errmsg;
    char sql[500] = "\0"; //写入命令
    strcpy(sql, "create table user(name text,password text);");
    ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_exec:");
        printf("errmsg:%s\n", errmsg);
        exit(2);
    }
    ret = sqlite3_close(db); //关闭数据库
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_close:");
        exit(3);
    }
    return;
}

int searchtable(char *tablename)
{
    sqlite3 *db = NULL;
    int ret = sqlite3_open("info.db", &db); //打开数据库
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_open:");
        exit(1);
    }
    char sql[200] = "\0";
    sprintf(sql, "select name from sqlite_master where type='table' AND name='%s';", tablename);
    char *errmsg;
    char **result;
    int row, column;
    ret = sqlite3_get_table(db, sql, &result, &row, &column, &errmsg); //分别为文件描述符，数据库命令，查询结果，行，列，错误信息
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_exec:");
        printf("errmsg:%s\n", errmsg);
        exit(2);
    }
    if (row >= 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    sqlite3_free_table(result); //释放内存
    ret = sqlite3_close(db);    //关闭数据库
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_close:");
        exit(3);
    }
}

void initdb()
{
    printf("正在进行初始化!\n");
    if (searchtable("user") == 0)
    {
        createtable();
    }
}

void carryout(char *sql)
{
    sqlite3 *db = NULL;
    int ret = sqlite3_open("info.db", &db); //打开数据库
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_open:");
        exit(1);
    }
    char *errmsg;
    ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_exec1:");
        printf("errmsg:%s\n", errmsg);
        exit(2);
    }
    ret = sqlite3_close(db); //关闭数据库
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_close:");
        exit(3);
    }
}

void updatedb(char *name, char *pw) //插入，修改数据库注册用户信息
{
    char sql[500] = "\0";
    sprintf(sql, "update user set password='%s' where name='%s';", pw, name); //插入，修改，删除都可以用这条语句
    carryout(sql);
}

void downdb(struct Node *head) //把已经注册的用户载入链表
{
    //printf("进入downdb\n");
    sqlite3 *db = NULL;
    int ret = sqlite3_open("info.db", &db); //打开数据库
    //printf("打开数据库\n");
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_open:");
        exit(1);
    }
    const char *sql = "select *from user;"; //写入命令
    //printf("写入命令\n");
    char *errmsg;
    char **result;
    int row = 0, column = 0;
    ret = sqlite3_get_table(db, sql, &result, &row, &column, &errmsg); //分别为文件描述符，数据库命令，查询结果，行，列，错误信息
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_exec:");
        printf("errmsg:%s\n", errmsg);
        exit(2);
    }
    printf("row=%d    column=%d\n", row, column);
    if (row == 0)
    {
        return;
    }
    int i, j;
    int num;
    char name[20] = "\0";
    char password[20] = "\0";
    printf("开始载入\n");
    for (i = 1; i <= row; i++)
    {
        for (j = 0; j < column; j++)
        {
            num = i * column + j;
            //printf("%s\n",result[num]);  //查询到的信息按一维数组的方式储存，0到2为id,name,age这些字段，3到5为第一行数据，6到8为第二行数据
            if (j == 0)
            {
                strcpy(name, result[num]);
            }
            if (j == 1)
            {
                strcpy(password, result[num]);
            }
        }
        insert(head, name, password);
    }
    sqlite3_free_table(result); //释放内存
    //printf("释放内存\n");
    ret = sqlite3_close(db); //关闭数据库
    //printf("关闭数据库\n");
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_close:");
        exit(3);
    }
    return;
}

int Function(struct client head) //聊天室功能选择
{
    //printf("msg:%s\n", head.msg);
    struct Forbit *p = F_head;
    struct Root *Root = r_head;
    struct user *all = h;
    struct Group *group = G_head;
    struct VIP *vip = V_head;

    int temp = head.root;
    int flag = seek_VIP(head.name);
    if (flag == 1)
    {
        head.root = 2;
    }

    if (-1 == head.flag)
    {
        delete_group(group, head.name); //退出群聊
    }
    else if (0 == head.flag) //发送给所有在线用户
    {
        while (all->next != NULL)
        {
            all = all->next;
            if (strcmp(all->name, head.name) == 0)
            {
                if (all->next != NULL)
                {
                    all = all->next;
                }
                else
                {
                    break;
                }
            }

            if (all->c_fd != 0)
            {
                send(all->c_fd, head.msg, sizeof(head.msg), 0);
            }
        }
    }
    else if (1 == head.flag) //私聊
    {
        char buf[500];
        int toc_fd = searchuser(h, head.to_name);
        if (toc_fd == 1)
        {
            toc_fd = searchuser(h, head.name);
            sprintf(buf, "\033[0;33m该用户未登录！\033[0m\n");
            send(toc_fd, buf, sizeof(head.msg), 0);
            memset(buf, 0, sizeof(buf));
        }
        else if (toc_fd == 0)
        {
            toc_fd = searchuser(h, head.name);
            sprintf(buf, "\033[0;31m该用户不存在！\033[0m\n");
            send(toc_fd, buf, sizeof(head.msg), 0);
            memset(buf, 0, sizeof(buf));
        }
        else
        {

            int flag1 = seek_Group(head.to_name); //查找发送用户是否处在群聊
            if (flag1 == 1)
            {
                sprintf(buf, "\033[34m%s\033[35m(私密消息)\033[36m：%s\033[0m\n", head.name, head.msg);
                strcpy(head.msg, buf);
                memset(buf, 0, sizeof(buf));
            }
            else
            {
                sprintf(buf, "\033[0;34m%s\033[36m：%s\033[0m\n", head.name, head.msg);
                strcpy(head.msg, buf);
                memset(buf, 0, sizeof(buf));
            }

            if (head.root == 2)
            {
                sprintf(buf, "\033[33m(VIP)%s", head.msg);
                strcpy(head.msg, buf);
                memset(buf, 0, sizeof(buf));
            }

            if (flag1 == 1)
            {
                sprintf(buf, "\033[5m%s", head.msg);
                strcpy(head.msg, buf);
                memset(buf, 0, sizeof(buf));
            }
            send(toc_fd, head.msg, sizeof(head.msg), 0);
        }
    }
    else if (head.flag == 2) //群聊
    {
        char buf[500];
        int t_fd;
        if (temp == -1) //进入群聊
        {
            insert_group(group, head.name);
            return 0;
        }
        int flag1 = seek_Group(head.name); //查找该用户是否为群成员
        if (flag1 == 1)
        {
            int c_fd = searchuser(h, head.name);
            int ret = seek_forbit(head.name);
            if (ret == 1) //该用户处于禁言状态
            {
                sprintf(buf, "\033[0;31m发送失败！你已被禁言！\033[0m\n");
                send(c_fd, buf, sizeof(buf), 0);
                memset(buf, 0, sizeof(buf));
                return 0;
            }
            if (head.root == 2)
            {
                sprintf(buf, "\033[0;33m(VIP)%s", head.msg);
                strcpy(head.msg, buf);
                memset(buf, 0, sizeof(buf));
            }
            while (group->next != NULL) //遍历所有群成员,，发送群消息
            {
                group = group->next;
                if (strcmp(group->name, head.name) == 0)
                {
                    if (group->next != NULL)
                    {
                        group = group->next;
                    }
                    else
                    {
                        break;
                    }
                }
                t_fd = searchuser(h, group->name);
                send(t_fd, head.msg, sizeof(head.msg), 0);
            }

            //记录聊天记录
            FILE *logs = fopen("log.txt", "a+");
            if (logs == NULL)
            {
                printf("open file erroe: \n");
            }
            else
            {
                fputs(head.msg, logs);
                fclose(logs);
            }
        }
        else
        {
            t_fd = searchuser(h, head.name);
            sprintf(buf, "\033[0;31m发送失败！你不是该群成员！\033[0m\n");
            send(t_fd, buf, strlen(buf) + 1, 0);
        }
    }
    else if (3 == head.flag) //文件传输
    {
        char buf[500];
        int toc_fd = searchuser(h, head.to_name);
        printf("%s向%s发送文件!\n", head.name, head.to_name);
        sprintf(buf, "\033[0;33m%s向你发来一份文件！\033[0m\n", head.name);
        send(toc_fd, buf, sizeof(buf), 0);
        usleep(30);
        memset(buf, 0, sizeof(buf));
        strcpy(buf, "flag==3");
        send(toc_fd, buf, strlen(buf) + 1, 0); //让客户端的进行文件接收准备
        memset(buf, 0, sizeof(buf));
        printf("文件内容:\n%s\n", head.msg);
        send(toc_fd, head.msg, sizeof(head.msg), 0); //发送文件内容
    }
    else if (4 == head.flag) //修改密码
    {
        int toc_fd = searchuser(h, head.name);
        printf("等待用户进行密码修改\n");
        int flag, flag1;
        char pw1[20] = "\0";
        char pw2[20] = "\0";
        char name[20] = "\0";

        read(toc_fd, pw1, 20);
        update_pw(head.name, pw1);
        updatedb(head.name, pw1);

        printf("用户密码修改成功\n");
    }
    else if (5 == head.flag)
    {
        char buf[500];
        int c_fd = searchuser(h, head.name);
        int toc_fd = searchuser(h, head.to_name);
        if (head.forbit == 1) //禁言
        {
            int count = 0;
            while (Root->next != NULL)
            {
                if (strcmp(Root->next->root, head.to_name) == 0)
                {
                    sprintf(buf, "\033[0;31m禁言失败！用户%s为管理员！\033[0m\n", head.to_name);
                    send(c_fd, buf, sizeof(buf), 0);
                    memset(buf, 0, sizeof(buf));
                    count++;
                    break;
                }
                Root = Root->next;
            }

            if (count == 0)
            {
                int flag1 = seek_VIP(head.to_name);
                if (flag1 == 1)
                {
                    sprintf(buf, "\033[0;31m禁言失败！用户%s为VIP用户！\033[0m\n", head.to_name);
                    send(c_fd, buf, sizeof(buf), 0);
                    memset(buf, 0, sizeof(buf));
                    count++;
                }
            }

            if (count == 0)
            {
                int ret = insert_forbit(p, head.to_name);
                if (ret == 1) //该用户已处于禁言状态
                {
                    sprintf(buf, "\033[0;31m禁言失败！用户%s已处于禁言状态，不可重复禁言！\033[0m\n", head.to_name);
                    send(c_fd, buf, sizeof(buf), 0);
                    memset(buf, 0, sizeof(buf));
                }
                else
                {
                    sprintf(buf, "\033[0;33m禁言成功！你已将用户%s禁言!\033[0m\n", head.to_name);
                    send(c_fd, buf, sizeof(buf), 0);
                    memset(buf, 0, sizeof(buf));

                    sprintf(buf, "\033[0;31m管理员%s将你禁言!\033[0m\n", head.name);
                    send(toc_fd, buf, sizeof(buf), 0);
                    memset(buf, 0, sizeof(buf));
                }
            }
        }
        else if (head.forbit == 2) //解除禁言
        {
            int ret1 = delete_forbit(p, head.to_name);

            if (ret1 == 1)
            {
                sprintf(buf, "\033[0;33m用户%s未被禁言！\033[0m\n", head.to_name);
                send(c_fd, buf, sizeof(buf), 0);
                memset(buf, 0, sizeof(buf));
            }
            else
            {
                sprintf(buf, "\033[0;33m解除成功！你已将用户%s解除禁言！\033[0m\n", head.to_name);
                send(c_fd, buf, sizeof(buf), 0);
                memset(buf, 0, sizeof(buf));

                sprintf(buf, "\033[0;33m你被管理员%s解除禁言!\033[0m\n", head.name);
                send(toc_fd, buf, sizeof(buf), 0);
                memset(buf, 0, sizeof(buf));
            }
        }
        else if (head.forbit == 3) //踢人
        {
            int count = 0;
            while (Root->next != NULL)
            {
                if (strcmp(Root->next->root, head.to_name) == 0)
                {
                    sprintf(buf, "\033[0;31m踢出群聊失败！用户%s为管理员！\033[0m\n", head.to_name);
                    send(c_fd, buf, sizeof(buf), 0);
                    memset(buf, 0, sizeof(buf));
                    count++;
                    break;
                }
                Root = Root->next;
            }

            if (count == 0)
            {
                int flag1 = seek_VIP(head.to_name);
                if (flag1 == 1)
                {
                    sprintf(buf, "\033[0;31m踢出群聊失败！用户%s为VIP用户！\033[0m\n", head.to_name);
                    send(c_fd, buf, sizeof(buf), 0);
                    memset(buf, 0, sizeof(buf));
                    count++;
                }
            }

            if (count == 0)
            {
                int ret = delete_group(group, head.to_name);
                if (ret == 1) //该用户不是该群成员
                {
                    sprintf(buf, "\033[0;31m踢出群聊失败！用户%s不是该群成员！\033[0m\n", head.to_name);
                    send(c_fd, buf, sizeof(buf), 0);
                    memset(buf, 0, sizeof(buf));
                }
                else
                {
                    sprintf(buf, "\033[0;33m用户%s已被你踢出群聊！\033[0m\n", head.to_name);
                    send(c_fd, buf, sizeof(buf), 0);
                    memset(buf, 0, sizeof(buf));

                    sprintf(buf, "\033[0;33m你被管理员%s踢出群聊!\033[0m\n", head.name);
                    send(toc_fd, buf, sizeof(buf), 0);
                    memset(buf, 0, sizeof(buf));
                }
            }
        }
    }
}

void *server_thread(void *p) //接收客户端结构体，并作出处理
{
    struct client head;
    struct user *c = h;
    struct i_fd tt = *(struct i_fd *)p;
    int i = tt.i;
    int fd = tt.c_fd;
    sem_wait(&sem1[i]);
    if (personalflag[0] == 0)
    {
        char user[50] = {};
        while (1)
        {
            char buf[100] = {};

            if (recv(fd, &head, sizeof(struct client), 0) <= 0)
            {
                while (c->next != NULL)
                {
                    c = c->next;
                    if (fd == c->c_fd)
                    {
                        c->c_fd = 0;
                        memset(c->name, 0, sizeof(c->name)); //初始化
                        break;
                    }
                }

                printf("\033[0;31m退出：%s 退出了聊天室.\033[0m\n", user);

                char buf[500];
                sprintf(buf, "\033[0;31m%s退出了聊天室. \033[0m\n", user);

                head.flag = 0;
                strcpy(head.name, user);
                strcpy(head.msg, buf);
                Function(head);

                FILE *logs = fopen("log.txt", "a");

                if (logs == NULL)
                {
                    printf("open file error: \n");
                }
                else
                {
                    fputs(buf, logs);
                    fclose(logs);
                }

                pthread_exit(0);
            }
            //把服务器接受到的信息发给所有的客户端
            strcpy(user, head.name); //记录进入群聊的用户

            Function(head);
        }
    }
}

int logon(int c_fd) //登录
{

    struct Root *root;
    root = r_head;

    printf("等待用户进行登录\n");
    int flag, flag1, flag2;
    char pw1[20] = "\0";
    char pw2[20] = "\0";
    char name[20] = "\0";
    read(c_fd, name, 20);
    printf("登录时接收到的用户名：%s\n", name);
    flag2 = search1(name); //检查该用户名是否已经进行注册
    write(c_fd, &flag2, sizeof(flag2));

    if (flag2 > 0) //已经注册，可以登录
    {
        flag1 = search2(name); //查找该用户是否已经登录
        printf("用户%s的登录状态：%d\n", name, flag1);
        write(c_fd, &flag1, sizeof(flag1));
        if (flag1 == 0)
        {
            int m_root = -1;
            read(c_fd, &m_root, sizeof(m_root));

            if (m_root == 1) //管理员模式登录
            {
                printf("\033[0;33m管理员模式登录中!\033[0m\n");
                int count = 0;
                while (root != NULL)
                {
                    if (strcmp(root->root, name) == 0)
                    {
                        write(c_fd, &m_root, sizeof(m_root));
                        count++;
                        printf("\033[0;33m管理员%s进入了聊天室!\033[0m\n", name);
                        break;
                    }
                    root = root->next;
                }
                if (count == 0) //该用户不是管理员
                {
                    printf("\033[0;33m该用户不是管理员!\033[0m\n");
                    m_root = 0;
                    write(c_fd, &m_root, sizeof(m_root));
                    logon(c_fd);
                }
            }
            read(c_fd, pw1, 20);
            search(name, pw2);
            if ((strcmp(pw1, pw2)) == 0)
            {
                flag = 1;
                write(c_fd, &flag, sizeof(flag));
                insert_tail(h, c_fd, name); //存入在线用户链表

                int vip = seek_VIP(name);
                printf("vip:%d\n", vip);
                write(c_fd, &vip, sizeof(vip));

                return 1;
            }
            else if ((strcmp(pw1, pw2)) != 0)
            {
                flag = 0;
                write(c_fd, &flag, sizeof(flag)); //让客服端重新进行用户登录
                logon(c_fd);
            }
        }
        else if (flag1 != 0)
        {
            printf("该用户已经登录，等待客户机重新输入\n");
            logon(c_fd);
        }
    }
    else if (flag2 == 0)
    {
        printf("该用户不存在，等待客户机重新输入\n");
        logon(c_fd);
    }
}

int register1(int c_fd) //注册
{
    char pw[20] = "\0";
    char name[20] = "\0";
    printf("等待客户机进行注册\n");
    read(c_fd, name, 20);
    printf("读取到用户名：%s\n", name);
    int flag = search1(name); //检查该用户名是否已经存在

    write(c_fd, &flag, sizeof(flag));

    if (flag == 0) //不存在，可以注册，读取密码
    {
        read(c_fd, pw, 20);
        struct Node *text = insert(h1, name, pw);
        printf("用户注册成功\n用户名：%s\n密码：%s\n", text->name, text->password);
        insertdb(text);
        return 1;
    }
    else if (flag == 1)
    {
        printf("用户名已存在，等待客户机重新输入\n");
        register1(c_fd);
    }
}

void *r_or_l(void *tt) //登录、注册
{

    struct i_fd *iandfd = (struct i_fd *)tt;
    int c_fd = iandfd->c_fd;
    int i = iandfd->i;
    int y = 0;
    int flag, flag1;
    while (1)
    {
        int ret = read(c_fd, &y, 4);
        if (y == 1)
        {
            flag = logon(c_fd); //登录成功返回1
            if (flag)
            {
                personalflag[i] = 0;
                sem_post(&sem1[i]); //成功则向聊天功能发送一个信号量，让其取消阻塞
                break;
            }
        }
        else if (y == 2)
        {

            register1(c_fd);
        }
    }
    pthread_join(pti1[i], NULL);
}

void server() //服务器开始工作
{
    int c_fd;
    struct user *head;    //用来存放已登录用户
    struct Node *head1;   //存放已注册用户
    struct Forbit *head2; //存放被禁言人员
    struct Root *head3;   //存放管理员名单
    struct Group *head4;  //存放群内成员
    struct VIP *head5;    //存放vip用户名单
    struct i_fd iandfd;
    init(&head);
    init1(&head1);
    initdb();
    downdb(head1);
    F_init(&head2); //创建禁言人员头节点
    r_init(&head3); //创建管理员用户头节点
    G_init(&head4); //创建群内成员用户头节点
    V_init(&head5); //创建VIP用户头节点
    h = head;
    h1 = head1;
    F_head = head2;
    r_head = head3;
    G_head = head4;
    V_head = head5;

    printf("服务器启动\n");
    int i = 0;
    while (1)
    {
        struct sockaddr_in fromaddr;
        socklen_t len = sizeof(fromaddr);
        int fd = accept(serverfd, (meng *)&fromaddr, &len);
        //调用accept进入堵塞状态，等待客户端的连接

        if (fd == -1)
        {
            printf("客户端连接出错...\n");
            continue;
        }
        printf("客服端连接成功\n");

        iandfd.i = i;
        iandfd.c_fd = fd;
        int ret = pthread_create(&pti1[i], NULL, r_or_l, (void *)&iandfd);
        if (ret != 0)
        {
            perror("pthread_create1:");
            exit(1);
        }
        sem_init(&sem[i], 0, 0);
        sem_init(&sem1[i], 0, 0);
        if (clientfd[i] == 0)
        {
            //记录客户端的socket
            clientfd[i] = fd;
            printf("线程号= %d\n", fd); //

            //有客户端连接之后，启动线程给此客户服务
            pthread_t tid;
            pthread_create(&tid, 0, server_thread, &iandfd);
        }

        if (size == i)
        {
            //发送给客户端说聊天室满了
            char *str = "\033[0;31m对不起，聊天室已经满了!\033[0m\n";
            send(fd, str, strlen(str), 0);
            close(fd);
        }
        i++;
    }
}

int main()
{
    system("clear");
    Init();   //初始化
    server(); //服务器开始工作
    close(serverfd);
    return 0;
}


