#include <iostream>
using namespace std;
class Singleton
{
public:
    static Singleton * getInstance()
    {
        if(p==nullptr){
            p=new Singleton();
        }
        return p;
    }
    static void destroy()
    {
        if(p){
            delete p;
        }
    }
    void print() const
    {
        cout<<"Singleton::print()"<<endl;
    }
private:
    Singleton(){cout<<"Singleton()"<<endl;}
    ~Singleton(){cout<<"~Singleton()"<<endl;}
private:
    static Singleton * p;
};
Singleton * Singleton::p=nullptr;
int main()
{
    Singleton * p1=Singleton::getInstance();
    Singleton * p2=Singleton::getInstance();
    cout<<"p1 = "<<p1<<endl
        <<"p2 = "<<p2<<endl;
    Singleton::getInstance()->print();
    Singleton::destroy();
    return 0;
}

