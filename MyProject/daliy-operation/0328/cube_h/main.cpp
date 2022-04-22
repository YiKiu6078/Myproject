#include "Cube.h"

int main(int argc, char const *argv[])
{
    Cube c1,c2;
    c1.get_date(1,2,3);
    c2.get_date(3,4,5);
    cout<<"c1的面积是："<<c1.area()<<endl;
    cout<<"c2的面积是："<<c2.area()<<endl;
    cout<<"c1的体积是："<<c1.volume()<<endl;
    cout<<"c2的体积是："<<c2.volume()<<endl;

    if (CubeIsQue(c1,c2))
    {
        cout<<"c1 = c2"<<endl;
    }
    else
    {
        cout<<"c1 != c2"<<endl;
    }
    return 0;
}
