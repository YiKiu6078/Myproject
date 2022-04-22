#include <iostream>
#include <cstring>
using namespace std;

class Sale
{
public:
    virtual void SaleBook() = 0;
};

class BookStore:public Sale
{
private:
    static int count;
public:
    void SaleBook()
    {
        cout<<"书店卖书"<<endl;
        count++;
    }
    static int Getcount()
    {
        return count;
    }
};

class Onlinestore:public Sale
{
private:
    Sale *sale;
public:
    Onlinestore(Sale *s)
    {
        sale = s;
    }
    void SaleBook()
    {
        cout<<"网上卖书"<<endl;
        sale->SaleBook();
    }
};

int BookStore::count = 0;

int main(int argc, char const *argv[])
{
    Sale * store = new BookStore;
    Sale * online = new Onlinestore(store);
    store->SaleBook();
    online->SaleBook();
    online->SaleBook();
    cout<<"卖出的书数量是："<<BookStore::Getcount()<<endl;
    return 0;
}
