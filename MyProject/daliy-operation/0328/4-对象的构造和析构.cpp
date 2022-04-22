#include <iostream>
using namespace std;

class Array
{
private:
    int *data;
    int size;
public:
    Array();//无参构造函数，函数名和类名一样
    Array(int a);
    Array(int a,int b);
    Array(const Array &a);
    void SetVal(int index,int val);
    int GetVal(int index);
    ~Array();
};

Array::Array()
{
    cout<<"第一个无参函数"<<endl;
    size = 5;
    data = (int*)malloc(sizeof(int*)*size);
}

Array::Array(int a)
{
    cout<<"size = "<<a<<endl;
    size = a;
    data = (int*)malloc(sizeof(int*)*size); 
    cout<<"有一个参数的构造函数"<<endl;
}

Array::Array(int a,int b)
{
    size = a;
    data = (int*)malloc(sizeof(int*)*size); 
    cout<<"有两个参数的构造函数"<<endl;
}

Array::Array(const Array &a)
{
    cout<<"Array的拷贝构造函数"<<endl;
}

void Array::SetVal(int index,int val)
{
    data[index] = val;
}

int Array::GetVal(int index)
{
    return data[index];
}

Array::~Array()
{
    cout<<"array 的析构函数"<<endl;
    if (data != NULL)
    {
        free(data);
    }
}

int main(int argc, char const *argv[])
{
    Array a1;
    for(int i = 0;i < 5;i++)
    {
        a1.SetVal(i,i+1);
    }
    for(int i = 0;i < 5;i++)
    {
        cout<<a1.GetVal(i)<<" ";
    }
    cout<<endl;

    cout<<"********************"<<endl;

    Array a2(10);
    for(int i = 0;i < 10;i++)
    {
        a2.SetVal(i,i+10);
    }
    for(int i = 0;i < 10;i++)
    {
        cout<<a2.GetVal(i)<<" ";
    }
    cout<<endl;

    cout<<"********************"<<endl;
    Array a3(10,8);
    //Array a3 = (10,8);
    //Array a3[2] = {11,8};
    cout<<"********************"<<endl;

    Array a4(a1);
    return 0;
}
