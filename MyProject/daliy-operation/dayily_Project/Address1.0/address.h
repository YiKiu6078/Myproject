#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NAME_MAX 20
#define SEX_MAX 5
#define ADDRESS_MAX 100

enum ret_val
{
    MALLOC_OK = 100,MALLOC_NO,DELETE_OK,DELETE_NO,QUIT_OK,QUIT_NO,
};

typedef struct link_information
{
    int num;
	char name[NAME_MAX];
	char sex[SEX_MAX];
	int age;
    int number;
	char addr[ADDRESS_MAX];

    struct link_information *next;
}Link_Infor;

typedef Link_Infor * Link;

int create_address(Link * address_list);
int create_address_number(Link * new_number_node);
void inser_information(Link address_list,Link new_number_node);
Link seek_address_number(Link address_list,int find);
int delete_number(Link address_list,int del_num);
void rev_number(Link address_list, Link rev_number_node,int rev_num);
void all_number(Link address_list);
int quit_address(Link * address_list);
