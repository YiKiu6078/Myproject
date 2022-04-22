#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>

#define PARK_MAX 5
#define SQL_MAX 100


int create_park(sqlite3 * park);
int create_stall(sqlite3 * park);
int view_park(sqlite3 * park);
int insert_park(sqlite3 * park,int* ret_time);
int delete_park(sqlite3 * park,int num,int ret_time,int * stay_time);
void count_money(sqlite3 * park,int num,int stay_time);
