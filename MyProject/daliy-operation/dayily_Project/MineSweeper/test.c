#include "game.h"

void menu()
{
    printf("**********************************************\n");
    printf("**********************************************\n");
    printf("******            1、play             ********\n");
    printf("******            0、exit             ********\n");
    printf("**********************************************\n");
    printf("**********************************************\n");
    printf("\n");
    
}

void game()
{
    printf("Minsweeper begins...\n");
    //1、雷的信息的布置
    char mine[ROWS][COLS] = {0};
    //2、雷的信息排查--显示雷的信息；
    char show[ROWS][COLS] = {0};
    //3、雷区的初始化
    char a = '0';
    char b = '*';
    //Initboard(mine,ROWS,COLS,a); 
    Initboard(show,ROWS,COLS,b); 
    //4、打印雷区
    Displayboard(mine,ROW,COL);
    Displayboard(show,ROW,COL);
    //5、设置雷区
    Setmine(mine,ROW,COL);
    Displayboard(mine,ROW,COL);  
    //6、扫雷
    Findmine(mine,show,ROW,COL);
}

void test()
{
    int input;
    srand((unsigned int)time(NULL));
    do
    {    
        menu();
        printf("please input select:\n");
        scanf("%d",&input);
        switch(input)
        {
            case 1:
                game();
                break;
            case 0:
                printf("exiting...\n");
                break;
            default:
                printf("input error!!!\n");
                break;
        }
        
    } while (input);
    

}

int main(int argc,char ** argv)
{
    test();
    return 0;
}