#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(int argc, char const *argv[])
{
    map<int,string> m;

    m.insert(pair<int,string>(1,"小"));
    m.insert(pair<int,string>(2,"思"));

    m.insert(make_pair(3,"菱"));
    m.insert(make_pair(4,"大"));

    m.insert(map<int,string>::value_type(5,"队"));
    m.insert(map<int,string>::value_type(6,"长"));

    m[7] = "老";
    m[8] = "冯";

    for(map<int,string>::iterator it = m.begin();it != m.end();it++)
    {
        cout<<"学号："<<it->first<<"姓名："<<it->second<<endl;
    }
    pair<map<int,string>::iterator,bool> p = m.insert(make_pair(8,"a"));
    if(p.second == false)
    {
        cout<<"插入失败"<<endl;
        cout<<"学号："<<p.first->first<<"姓名："<<p.first->second<<endl;
        cout << "******************" << endl;
    }
    else
    {
        cout<<"插入成功"<<endl;
    }

    cout<<"map删除指定位置"<<endl;
    m.erase(m.begin());
    for(map<int,string>::iterator it = m.begin();it != m.end();it++)
    {
        cout<<"学号："<<it->first<<"姓名："<<it->second<<endl;
    }
    cout<<"删除一个区间"<<endl;
    m.erase(--(m.end()),m.end());
    for(map<int,string>::iterator it = m.begin();it != m.end();it++)
    {
        cout<<"学号："<<it->first<<"姓名："<<it->second<<endl;
    }

    cout<<"删除具体元素"<<endl;
    m.erase(7);
    for(map<int,string>::iterator it = m.begin();it != m.end();it++)
    {
        cout<<"学号："<<it->first<<"姓名："<<it->second<<endl;
    }
    return 0;
}
