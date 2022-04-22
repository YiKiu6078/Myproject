#ifndef _MYHEAD_H_
#define _MYHEAD_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sqlite3.h>
#include <string.h>

#define DEFAULT				 "\e[0m"
//#define NONE                 "\e[0m"
#define BLACK                "\e[0;30m"
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
#define WHITE                "\e[1;37m"
#define BOLD                 "\e[1m"
#define UNDERLINE            "\e[4m"
#define BLINK                "\e[5m"
#define REVERSE              "\e[7m"
#define HIDE                 "\e[8m"
#define CLEAR                "\e[2J"
#define CLRLINE              "\r\e[K" //or "\e[1K\r"

#define MYPORT 2333   //1024以下是保留的端口号，用大于1024的端口号
#define MYADDR "192.168.171.131"
extern char ssid[20];

#define F 0;
#define T 1;

extern int have_flag;
//char ssid = {0};






struct message
{
	int action;     //order
	int toid;       //receive id
	int fromid;     //send id
	char buff[200];  //data
	int backid;
	int admin;
	char user[20];
	int kick;
	
	char name[20];
	char key[20];
	char id[20];	

};






struct online  
{
	char id[20];
	char name[20];
	int fd;
	int forbid;
	struct online *next;
};

typedef struct online* Node;


void create_table(sqlite3 *db);
int open_db(sqlite3 **db);
void input(sqlite3 *db,int fd,struct message Msg);
void find(sqlite3 *db, int id,int fd, struct message Msg);
void findreg(sqlite3 *db, int id,int fd, struct message Msg);
void input1(sqlite3 *db,int fd,struct message Msg);



#endif
