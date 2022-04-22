#include <iostream>
#include <stack>
#include <time.h>
using namespace std;

int main(int argc, char const *argv[])
{
    stack<int> s;
    srand(time(NULL));

    int num;
    for(int i = 0;i < 10;i++)
    {
        num = rand()%10;
        s.push(num);
        cout<<num<<" 进栈成功"<<endl;
    }
    cout<<"栈顶元素为: "<<s.top()<<endl;
    cout<<"栈大小为: "<<s.size()<<endl;

    while(!s.empty())
    {
        cout<<s.top()<<"出栈"<<endl;
        s.pop();
    }
    return 0;
}
