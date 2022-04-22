#include <iostream>
#include <cstring>
using namespace std;

class House
{
private:
    string window;
    string door;
    string wall;
public:
    void SetWindow(string w)
    {
        window = w;
    }
    void SetWall(string wa)
    {
        wall = wa;
    }
    void SetDoor(string d)
    {
        door = d;
    }
};

class Builder
{
protected:
    House * house;
public:
    virtual void construct () = 0;
};

class CommonBuilder:public Builder
{
public:
    CommonBuilder(House * h)
    {
        house = h;
    }
    void construct()
    {
        cout<<"开始建造普通房子"<<endl;
        house->SetDoor("DOOR");
        house->SetWall("WALL");
        house->SetWindow("WINDOW");
    }

};

class VilliaBuilder:public Builder
{
public:
    VilliaBuilder(House * h)
    {
        house = h;
    }
    void construct()
    {
        cout<<"开始建造别墅"<<endl;
        house->SetDoor("VilliaDOOR");
        house->SetWall("VilliaWALL");
        house->SetWindow("VilliaWINDOW");
    }
};

class Designer
{
private:
    Builder *b;
public:
    void SetBuilder(Builder *builder)
    {

        b = builder;
    }
    void Constructor()
    {
        b->construct();
    }
};

int main(int argc, char const *argv[])
{
    House *h = new House;
    Designer * d = new Designer;
    Builder *b = new CommonBuilder(h);
    d->SetBuilder(b);
    d->Constructor();  
    delete b;
    b = new VilliaBuilder(h);
    d->SetBuilder(b);
    d->Constructor();
    return 0;
}
