#include <iostream>
using namespace std;

class Circle
{
private:
    int m_r;
    double m_s;
public:
    void SetR(int r)
    {
        m_r = r;
    }
    double GetS()
    {
        m_s = 3.14 * m_r * m_r;
    }
};

int main(int argc, char const *argv[])
{
    Circle c1;
    c1.SetR(3);
    cout<<c1.GetS()<<endl;
    return 0;
}
