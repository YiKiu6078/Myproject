#include <iostream>
using namespace std;

class Array
{
    private:
        int *date;
        int size;
    public:
        Array(int a)  //初始化
        {
            size = a;
            date = new int[size];
        }

        bool operator==(const Array &a)  
        {
         /*   if (this->size != a.size)
            {
                return false;
            }
            for (int i = 0;i < size;i++)
            {
                if (this->date[i] != a.date[i])
                {
                    return false;
                }
            }
            return true;
        */
            return (this->size == a.size) && (this->date == a.date);
        }

        int &operator[](int Index)
        {
            return date[Index];
        }

        Array &operator=(const Array &a)
        {
            if (*this == a)
            {
                return *this;
            }
            this->size = a.size;
            delete []date;  //先将date清空
            this->date = new int[this->size];
            for(int i = 0;i < a.size;i++)
            {
                this->date[i] = a.date[i];
            }

        }
        ~Array()
        {
            delete []date;
            date = NULL;
        }
};

int main(int argc, char const *argv[])
{
    Array a1(100);
    for(int i = 0;i < 10;i++)
    {
        a1[i] = i + 1;  //'[]'需要重载  ，'=' 需要重载
    }
    for (int i = 0;i < 10;i++)
    {
        cout<<a1[i]<<" ";
    }
    cout<<endl;

    Array a2(5);
    for(int i = 0;i < 5;i++)
    {
        a2[i] = i + 1;
    }
    a1 = a1;
    for(int i = 0;i < 10;i++)
    {
        cout<<a1[i]<<" ";
    }
    cout<<endl;
    return 0;
}
