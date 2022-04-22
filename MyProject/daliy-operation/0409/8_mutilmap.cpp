#include <iostream>
#include <string>
#include <map>
using namespace std;

class Employee
{
private:
    int id;
    string name;
public:
    Employee(int i,string s)
    {
        id = i;
        name = s;
    }
    void show()
    {
        cout<<"工号："<<id<<"姓名："<<name<<endl;
    }
};

int main(int argc, char const *argv[])
{
    Employee e1(1,"a");
    Employee e2(2,"b");
    Employee e3(3,"c");
    Employee e4(4,"d");
    Employee e5(5,"e");
    Employee e6(6,"f");

    multimap<string,Employee> m;
    m.insert(make_pair("sale",e1));
    m.insert(make_pair("sale",e2));
    m.insert(make_pair("sale",e3));

    m.insert(make_pair("Researcher",e4));

    m.insert(make_pair("Finance",e5));
    m.insert(make_pair("Finance",e6));

    cout<<m.count("sale")<<endl;
    for (multimap<string,Employee>::iterator it = m.begin();it != m.end();it++)
    {
        cout<<"部门： "<<it->first<<endl;
        it->second.show();
    }
    return 0;
}
