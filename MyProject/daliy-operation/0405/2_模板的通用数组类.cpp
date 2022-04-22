#include <iostream>
using namespace std;

template <typename T>
class Myarry
{
private:
    T * pAddress;
    int m_Capacity;
    int m_size;
public:
    Myarry(int Capacity)
    {
        cout<<"Myarry 的有参构造"<<endl;
        this->m_Capacity = Capacity;
        this->m_size = 0;
        this->pAddress = new T[this->m_Capacity];
    }

    Myarry(const Myarry& arr)
    {
        cout<<"Myarry 的拷贝构造"<<endl;
        this->m_Capacity = arr.m_Capacity;
        this->m_size = arr.m_size;
        this->pAddress = new T[arr.m_Capacity];
        for(int i = 0;i < m_size;i++)
        {
            this->pAddress[i] = arr.pAddress[i];
        }
    }

    Myarry& operator=(const Myarry& arr)
    {
        cout<<"Myarry 的operator函数调用"<<endl;
        if (this->pAddress != NULL)
        {
            delete []this->pAddress;
            this->pAddress = NULL;
            this->m_Capacity = 0;
            this->m_size = 0;
        }
        this->m_Capacity = arr.m_Capacity;
        this->m_size = arr.m_size;
        this->pAddress = new T[arr.m_Capacity];
        for(int i = 0;i < m_size;i++)
        {
            this->pAddress[i] = arr.pAddress[i];
        }
        return *this;
    }

    void push_tail(const T& val)
    {
        this->pAddress[this->m_size] = val;
        this->m_size++;
        if (this->m_Capacity = this->m_size)
        {
            return ;
        }
    }

    void pop_tail()
    {
        if(this->m_size == 0)
        {
            return ;
        } 
        this->m_size--;
    }

    int GetCapacity()
    {
        return this->m_Capacity;
    }

    int GetSize()
    {
        return this->m_size;
    }

    void printarry(Myarry<int> &arr)
    {
        for (int i = 0;i < arr.GetSize();i++)
        {
            cout<<arr[i]<<endl;
        }
    }

    T& operator[](int index)
    {
        return this->pAddress[index];
    }

    ~Myarry()
    {
        cout<<"Myarry 的析构函数调用"<<endl;
        if (this->pAddress != NULL)
        {
            delete []pAddress;
            this->pAddress = NULL;
        }
    }
};



int main(int argc, char const *argv[])
{
    Myarry<int> arr1(5);
//    Myarry<int> arr2(arr1);
//    Myarry<int> arr3(10);
//    arr3 = arr1;
    for(int i = 0;i < 6;i++)
    {
        arr1.push_tail(i);
    }
    arr1.printarry(arr1);
    cout<<"arr1的容量为"<<arr1.GetCapacity()<<endl;
    cout<<"arr1的大小为"<<arr1.GetSize()<<endl;
    return 0;
}
