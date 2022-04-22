#ifdef _POINT_H_
#define _POINT_H_
#include <iostream>
using namespace std;

class Point
{
private:
    int m_x;
    int m_y;
public:
    int GetX();
    int GetY();
    void SetXY(int x,int y);
    int Distance(Point &p);
};

class Circle
{
private:
    int m_r;
    Point m_center;
public:
    int SetC(int x,int y,int m_r);
    int judge(Point &p);
};

#endif