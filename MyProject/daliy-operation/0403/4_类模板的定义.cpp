#include <iostream>
using namespace std;

template<typename T,typename U>

class Test
{
private:
    T a;
    U b;
public:
    Test (T a,U b)
    {
        this->a = a;
        this->b = b;
    }
    void show()
    {
        cout<<a<<" "<<b<<endl;
    }
};

int main(int argc, char const *argv[])
{
    Test<int,char> t(1,'a');
    t.show();
    return 0;
}
