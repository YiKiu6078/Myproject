#include <iostream>
#include <cstring>
using namespace std;

class House
{
private:
    string m_Windows;
    string m_Door;
    string m_Wall;
public:
    void SetWindows()
    {
        m_Windows = "Windows";
        cout<<"开始建造："<<m_Windows<<endl;
    }
    void SetWall()
    {
        m_Wall = "Wall";
        cout<<"开始建造："<<m_Wall<<endl;
    }
    void SetDoor()
    {
        m_Door = "Door";
        cout<<"开始建造："<<m_Door<<endl;
    }
};

class Bulider
{
private:
    House *h;
public:
    Bulider(House *house)
    {
        this->h = house;
    }
    void CreateHouse()
    {
        h->SetWall();
        h->SetDoor();
        h->SetWindows();
    }
};

int main(int argc, char const *argv[])
{
    House *h = new House;
    Bulider *b = new Bulider(h);
    b->CreateHouse();
    return 0;
}
