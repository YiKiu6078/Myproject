#include <iostream>
using namespace std;

struct Chinese
{
    char msg[32];
    void func()
    {

    }
};

void func(struct Chinese * msg)
{
    printf("他说了一句%s\n",msg->msg);
}

int main(int argc, char const *argv[])
{
    Chinese ch = {"what's up"};
    func(&ch);
    return 0;
}
