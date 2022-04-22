#include <iostream>
#include <queue>
using namespace std;

int main(int argc, char const *argv[])
{
    queue<int> q;
    for(int i = 0;i < 10;i++)
    {
        q.push(i);
        cout<<i<<" 入队成功"<<endl;
    }
    cout<<"队头元素为 "<<q.front()<<endl;
    cout<<"队尾元素为 "<<q.back()<<endl;

    cout<<"队列大小为 "<<q.size()<<endl;

    while(!q.empty())
    {
        cout<<q.front()<<" 出队"<<endl;
        q.pop();
    }
    return 0;
}
