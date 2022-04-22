#include <iostream>
#include <queue>
using namespace std;

int main(int argc, char const *argv[])
{
 //   priority_queue<int> p;  //默认从大到小排序出队列；
 //   priority_queue<int,vector<int>,less<int>> p;  //等同于priority_queue<int> p；
    priority_queue<int,vector<int>,greater<int>> p;  //从小到大排序出队；
    srand(time(NULL));
    int num;
    for(int i = 0;i < 10;i++)
    {
        num = rand()%10;
        p.push(num);
        cout<<num<<" 入队成功"<<endl;
    }
    cout<<"队头元素为 "<<p.top()<<endl;
    cout<<"队列大小为 "<<p.size()<<endl;

    while(!p.empty())
    {
        cout<<p.top()<<" 出队"<<endl;
        p.pop();
    }
    return 0;
}
