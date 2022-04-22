#include "Point.h"

int main(int argc, char const *argv[])
{
    Point p;
    p.SetXY(0,0);
    p.Distance(p);

    Circle c;
    c.SetC(0,0,1);

    if (c.judge(p))
    {
        cout<<"点在圆内或圆上"<<endl;
    }
    else
    {
        cout<<"点在圆外"<<endl;
    }
    return 0;
}
