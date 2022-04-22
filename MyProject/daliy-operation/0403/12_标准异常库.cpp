#include <iostream>
#include <exception>
using namespace std;

class Test
{
public:
    Test(int i)
    {
        if (i < 0)
        {
            throw out_of_range("id 不能小于0");
        }
        id = i;
    }
private:
    int id;
};

int main(int argc, char const *argv[])
{
    try
    {
        Test t(-1);
    }
    catch(const std::exception& e)
    {
        cout<<e.what()<<endl;
    }
    
    return 0;
}
