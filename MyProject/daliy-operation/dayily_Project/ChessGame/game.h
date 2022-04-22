#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define ROW 3
#define COL 3


void InitBoard(char board[ROW][COL], int row, int col);//在头文件中声明初始数组化的函数；
void DisplayBoard(char board[ROW][COL],int row,int col);
void PlayerMove(char board[ROW][COL], int row,int col);
void ComputerMove(char board[ROW][COL], int row,int col);
char IsWin(char board[ROW][COL], int row,int col);//判断输赢；1、玩家赢了'*'2、电脑赢了'#'3、平局'Q'4、继续游戏'C'.
