#ifndef _CUBE_H_
#define _CUBE_H_
#include <iostream>
using namespace std;

class Cube
{
private:
    int m_length;
    int m_wide;
    int m_hight;
public:
    void get_date(int length,int wide,int hight);
    int area();
    int volume();
    int GetLength();
    int GetHight();
    int GetWide();
};

bool CubeIsQue(Cube c1,Cube c2);
#endif
