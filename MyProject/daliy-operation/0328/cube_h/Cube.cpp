#include "Cube.h"

void Cube::get_date(int length,int wide,int hight)
{
    m_length = length;
    m_hight = hight;
    m_wide = wide;
}

int Cube::area()
{
    return 2 * m_length * m_wide + 2 * m_length * m_hight + 2 * m_hight * m_wide;
}

int Cube::volume()
{
    return m_length * m_wide * m_hight;
}

int Cube::GetLength()
{
    return m_length;
}

int Cube::GetHight()
{
    return m_hight;
}

int Cube::GetWide()
{
    return m_wide;
}

bool CubeIsQue(Cube c1,Cube c2)
{
    if (c1.GetHight() == c2.GetHight() && c1.GetLength() == c2.GetLength() && c1.GetWide() == c2.GetWide())
    {
        return true;
    }
    else 
    {
        return false;
    }
}