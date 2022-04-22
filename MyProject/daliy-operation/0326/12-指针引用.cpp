#include <iostream>
#include <string.h>
using namespace std;

struct student
{
    int id;
    char name[32];
};

void getMemory(student *&p)
{
    p = (student *)malloc(sizeof(student));
    if (p == NULL)
    {
        return ;
    }
    p->id = 100;
    strcpy(p->name,"laofeng");
}

int main(int argc, char const *argv[])
{
    student * ptr = NULL;
    getMemory(ptr);
    cout<<"id = "<<ptr->id<<"name = "<<ptr->name<<endl;
    return 0;
}
