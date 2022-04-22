#include <iostream>
#include <list>
using namespace std;

class iFile
{
public:
    virtual string GetName() = 0;
    virtual int Add(iFile *file) = 0;
    virtual int Remove(iFile *file) = 0;
    virtual list<iFile *> *GetChild() = 0;
};

class File:public iFile
{
private:
    string name;
public:
    File(string n)
    {
        name = n;
    }
    string GetName()
    {
        return name;
    }
    int Add(iFile * file)
    {
        return -1;
    }
    int Remove(iFile * file)
    {
        return -1;
    }
    list<iFile *>*GetChild()
    {
        return NULL;
    }
};

class Dir:public iFile  //目录
{
private:
    string name;
    list<iFile*> *l;
public:
    Dir(string n)
    {
        name = n;
        l = new list<iFile *>;
    }
    string GetName()
    {
        return name;
    }
    int Add(iFile * file)
    {
        l->push_back(file);
        return 1;
    }
    int Remove(iFile * file)
    {
        l->remove(file);
        return -1;
    }
    list<iFile *>*GetChild()
    {
        return l;
    }

};

void show(iFile *root,int gap)
{
    for (int i = 0;i < gap;i++)
    {
        cout<<"---";

    }
    if (root != NULL)
    {
        cout<<root->GetName()<<endl;
    }
    else
    {
        return;
    }
    list<iFile *>* l = root->GetChild();
    if (l != NULL)
    {
        for( list<iFile*>::iterator it = l->begin();it != l->end();it++)
        {
            show((*it),gap + 1);
        }
    }
}

int main(int argc, char const *argv[])
{
    iFile *dir1 = new Dir("207");
    iFile *dir2 = new Dir("day1");
    iFile *dir3 = new Dir("day2");
    iFile* file1 = new File("1.cpp");
    iFile* file2 = new File("2.cpp");
    iFile* file3 = new File("3.cpp");
    iFile* file4 = new File("4.cpp");
    iFile* file5 = new File("5.cpp");

    dir1->Add(dir2);
    dir1->Add(dir3);
    dir2->Add(file1);
    dir2->Add(file2);
    dir2->Add(file3);
    dir2->Add(file4);
    dir3->Add(file2);
    dir3->Add(file3);
    dir3->Add(file4);
    dir3->Add(file5);
    show(dir1,0);
    return 0;
}
