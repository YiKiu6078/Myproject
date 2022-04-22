#include<stdio.h>
#include"game.h"
void game()
{
    char ret;
	char board[ROW][COL]={0};
    InitBoard(board,ROW,COL);//数组初始化；
	DisplayBoard(board,ROW,COL);//打印棋盘；
	while(1)
	{
	    PlayerMove(board,ROW,COL);// 玩家下棋
	    DisplayBoard(board,ROW,COL);//打印棋盘
		ret = IsWin(board,ROW,COL);
  		if(ret != 'C')
		{
		    break;
		}
		ComputerMove(board,ROW,COL);//电脑下棋
	    DisplayBoard(board,ROW,COL);//打印棋盘
		ret = IsWin(board,ROW,COL);
  		if(ret != 'C')
		{
		    break;
		}
	}
	if(ret = '*')
	{
	    printf("The player win!!!\n");
	}
	else if(ret = '#')
	{
	    printf("The player loses!!!\n");
	}
	else
	{
	    printf("Dogfall!!!\n");
	}
}
void menu()
{
    printf("------------------------------------\n");
    printf("----- 1、进入游戏  2、退出游戏------\n");
    printf("------------------------------------\n");
}
void test()
{
	srand((unsigned int)time(NULL));
	int enter=0;
	do
	{
        menu();
	    printf("please enter number 1 or 2!!!\n");
	    scanf("%d",&enter);
		switch(enter)
		{
		    
	        case 1:
		        printf("进入游戏中......\n");
		        game();
				break;
	        case 2:
		        printf("正在退出游戏......\n");
		        break;
	        default:
		        printf("输入有误，请重新输入！！！\n");
		        break;
		}
	}
	while(enter);
}
int main()
{
	test();
    return 0;
}
