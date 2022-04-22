#include <iostream>
using namespace std;

class student
{
public:    //加上1个public表示公有类
    int age;
    char *name;
    void printf()
    {
        cout<<"name = "<<name<<"age ="<<age<<endl;
    }
};

int main(int argc, char const *argv[])
{
    student s1;
    s1.name = "what's up";
    s1.age = 18;
    s1.printf();
    return 0;
}
