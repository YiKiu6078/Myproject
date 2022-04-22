#include"game.h"
void InitBoard(char board[ROW][COL],int row,int col)
{
    int i,j;
	for(i=0;i<row;i++)
	{
	    for(j=0;j<col;j++)
		{
		    board[i][j]=' ';
		}
	}
}
void DisplayBoard(char board[ROW][COL],int row,int col)
{
    int i;
	int j=0;
	for(i=0;i<row;i++)
	{
	    for(j=0;j<col;j++)
		{
		    printf(" %c ",board[i][j]);
			if(j<col-1)
			{
			    printf("|");
			}
		}
		printf("\n");
        if(i<row-1)
		{
		    for(j=0;j<col;j++)
			{
			    printf("---");
				if(j<col-1)
				{
					printf("|");
				}
			}
			printf("\n");
		}
	}
}
void PlayerMove(char board[ROW][COL],int row,int col)
{
    printf("玩家开始游戏！！！\n");
	int x,y;
    while(1)
	{    
		printf("请输入行和列号：\n");
	    scanf("%d%d",&x,&y);
	    if(x>=1&&x<=row||y>=1&&y<=col)
	    {
	        if(board[x-1][y-1]==' ')
			{
			    board[x-1][y-1]='*';
				break;
			}
			else
			{
			    printf("这个地方已经下过了！！！\n");
			}
	    }
	    else
	    {
	        printf("sorry,你输错了！！！please input again!!!\n");
	    }
    }
}

void ComputerMove(char board[ROW][COL], int row,int col)
{
    int x=0;
	int y=0;
	printf("电脑走->\n");
	while(1)
	{
	    x=rand()%ROW;
		y=rand()%COL;
		if(board[x][y] == ' ')
		{
		    board[x][y] = '#';
			break;
		}
	}
}
int IsFull(char board[ROW][COL],int row,int col)
{
    int i,j;
	for (i = 0;i < row;i++)
	{
		for (j = 0;j < col;j++)
		{
	        if (board[i][j] = ' ')
			{
			    return 0;
			}
		}
	}
	return 1;
}
char IsWin(char board[ROW][COL], int row,int col)
{
    int i = 0;
	for ( i = 0;i < ROW; i++)
	{
	    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ')
		{
		    return board[i][1];
		}
	}
	for ( i = 0;i < ROW; i++)
	{
	    if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != ' ')
		{
		    return board[i][1];
		}
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
	{
  	    return board[1][1];
	}
	if (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[1][1] != ' ')
	{
  	    return board[1][1];
	}
	if (1 == IsFull(board,ROW,COL))
	{
	    return 'Q';
	}
	return 'C';
	
}
