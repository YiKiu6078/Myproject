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
#define NAME_SIZE 32
#define MSG_SIZE 100


enum{
    SQLITE_NO = -1,
    REG_OK = 100,  //注册成功
    LOG_OK,LOG_NO,  //登录成功失败
    MALLOC_OK,MALLOC_NO,  //动态空间分配成功/失败
    CREATE_NODE_OK,CREATE_NODE_NO,  //节点创建成功/失败
    ONLINE,OFFLINE,    //用户在线/下线
    EXIST_OK,EXIST_NO,  //在线链表存在用户/不存在
    CHANGE_OK,CHANGE_NO,  //修改密码成功/失败
    FORB_OK,FORB_NO,   //禁言成功、失败
    SEEK_OK,SEEK_NO,  //查看所有在线用户成功/失败
    MSG_OK,MSG_NO,  //可以发送消息/不可以
    CAN_SAY_OK,CAN_SAY_NO, //解除禁言成功/失败
    KICK_OUT_OK,KICK_OUT_NO, //踢除成功，失败
    FORCE_OFFLINE,    //强制下线
    SEND_FILE_OK,SEND_FILE_NO,  //发送文件成功，失败
    RECV_FILE,    //接收文件标志
    };

int line = 8; //打印消息时候的行数
int frame = 0; //是否在聊天框内 0:处在功能选择 1:处在聊天框
