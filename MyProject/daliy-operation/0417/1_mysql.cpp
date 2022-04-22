#include <iostream>
#include <mysql/mysql.h>
#include <iomanip>
using namespace std;

MYSQL *Init()
{
    MYSQL *m;
    m = mysql_init(NULL);  //返回的是对象的地址；
    if (NULL == m)
    {

        cout<<mysql_error(m)<<endl;
        return NULL;
    }
    m = mysql_real_connect(m,"localhost","YiKiu","yikiu","mydatabase",0,NULL,0);
    if (NULL == m)
    {

        cout<<mysql_error(m)<<endl;
        return NULL;
    }
    return m;
}

void InsertDataBase(MYSQL *m)
{
    if (NULL == m)
    {
        return ;
    }
    int ret = mysql_query(m,"set names utf8;");
    if (ret != 0)
    {
        cout<<mysql_error(m)<<endl;
        return;
    }
    cout<<"请输入编号，姓名，出生日期，年龄，性别，电话："<<endl;
    char sql[128] = {0};
    int id,age;
    char name[32] = {0},birth[32] = {0},sex[32] = {0},tel[32] = {0};
    cin>>id>>name>>birth>>age>>sex>>tel;
    sprintf(sql,"insert into stu(id,name,birth,age,sex,tel) values (%d,'%s','%s',%d,'%s','%s');",id,name,birth,age,sex,tel);
    cout<<sql<<endl;
    ret = mysql_query(m,sql);
    if (ret != 0)
    {
        cout<<mysql_error(m)<<endl;
        return ;
    }
    cout<<"insert success"<<endl;
}

void FindDataBase(MYSQL *m)
{
    if(m == NULL)
    {
        return;
    }
    int ret = mysql_query(m,"set names utf8;");
     if(0 != ret)
    {
        cout<<mysql_error(m)<<endl;
        return;
    }
    ret = mysql_query(m,"select * from stu");
    if(0 != ret)
    {
        cout<<mysql_error(m)<<endl;
        return;
     }
    MYSQL_RES *res = mysql_store_result(m);  //获取查询到的结果
    if(NULL == res)
    {
        cout<<mysql_error(m)<<endl;
        return; 
    }
    //获取字段数
    int field = mysql_num_fields(res);
    cout<<field<<endl;
    MYSQL_FIELD *f;
    while(f = mysql_fetch_field(res))
    {
        cout<<setw(20)<<setiosflags(ios::left)<<f->name;  //打印字段名
    }
    cout<<endl;
    //获取每一条记录
    MYSQL_ROW r;
    while(r = mysql_fetch_row(res))
    {
        for(int i = 0; i < field;i++)
        {
            cout<<setw(20)<<setiosflags(ios::left)<<r[i];
        }
        cout<<endl;
    }
}

int main(int argc, char const *argv[])
{
    MYSQL *mysql;
    mysql = Init();
    if (NULL == mysql)
    {
        cout<<"初始化mysql失败"<<endl;
    }
    else
    {
        cout<<"连接数据库成功"<<endl;
    }
    InsertDataBase(mysql);
    FindDataBase(mysql);
    return 0;
}
