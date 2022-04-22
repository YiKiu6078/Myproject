#include <iostream>
using namespace std;

template <typename T>
void mySwap(T &a,T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void mySort(T arr[],int len)
{
    for(int i = 0;i < len;i++)
    {
        int max = i;
        for(int j = i + 1;j < len;j++)
        {
            if (arr[max] < arr[j])
            {
                max = j;
            }
            if (max != i)
            {
                mySwap(arr[max],arr[i]);
            }
        }
    }
}

template <typename T>
void printArry(T arr[],int len)
{
    for (int i = 0;i < len;i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    char chararry[] = "adsceg";
    int len = sizeof(chararry) / sizeof(char);
    mySort(chararry,len);
    printArry(chararry,len);
    cout << "________________" << endl;

    int intarry[] = {1,9,3,5,2,6,4,7,8};
    len = sizeof(intarry) / sizeof(int);
    mySort(intarry,len);
    printArry(intarry,len);
    return 0;
}
