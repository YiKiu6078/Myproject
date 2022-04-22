#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sqlite3.h>

#define NAME_SIZE 1024 //定义姓名空间大小
#define SEX_SIZE 200  // 性别
#define NUM_SIZE 1024  //电话
#define ADR_SIZE 1024  //地址
#define SQL_SIZE 1024  //SQL语句大小

int create_address(sqlite3 * adr);
int insert_scord(sqlite3 * adr);
int delete_scord(sqlite3 * adr);
int update_scord(sqlite3 * adr);
int inquire_scord(sqlite3 * adr);
int inquire_all_scord(sqlite3 * adr);
