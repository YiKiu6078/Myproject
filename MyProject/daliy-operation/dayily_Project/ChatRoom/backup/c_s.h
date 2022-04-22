#include <stdio.h>
#include <unistd.h>
#include <sqlite3.h>
#include <pthread.h>
#include <sys/fcntl.h>
#include <time.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERVPORT 8888    //定义端口号
#define SQL_SIZE 100


enum{SQLITE_NO = -1,REG_OK = 100,LOG_OK,LOG_NO,MALLOC_OK,MALLOC_NO,CREATE_NODE_OK,CREATE_NODE_NO,ONLINE,OFFLINE};

int line = 8; //打印消息时候的行数
int frame = 0; //是否在聊天框内 0:处在功能选择 1:处在聊天框
