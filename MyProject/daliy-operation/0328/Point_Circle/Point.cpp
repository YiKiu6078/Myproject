#include "Point.h"

int Point::GetX()
{
    return m_x;
}

int Point::GetY()
{
    return m_y;
}

void Point::SetXY(int x,int y)
{
    m_x = x;
    m_y = y;
}

int Point::Distance(Point &p)
{
    int dis = (p.m_x - m_x) * (p.m_x - m_x) + (p.m_y - m_y) * (p.m_y - m_y);

    return dis;
}

int Circle::SetC(int x,int y,int r)
{
    m_center.SetXY(x,y);
    m_r = r;
}

bool Circle::judge(Point &p)
{
    if (p.Distance(m_center) <= m_r * m_r)
    {
        return true;
    }
    else
    {
        return false;
    }
}