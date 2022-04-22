#include <iostream>
using namespace std;

class Animal
{
public:
/*    virtual void speek()
    {
        cout<<"Animal speek"<<endl;
    }

*/
    void speek()
    {
        cout<<"Animal speek"<<endl;
    }
};

class Cat:public Animal
{
public:
    void speek()
    {
        cout<<"Cat speek"<<endl;
    }
};

class Dog:public Animal
{
public:
    void speek()
    {
        cout<<"Dog speek"<<endl;
    }
};

void doSpeek(Animal &animal)
{
    animal.speek();
}

int main(int argc, char const *argv[])
{
    Cat cat;
    doSpeek(cat);

    cout<<sizeof(Animal)<<endl;
    return 0;
}
