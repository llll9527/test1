#include <iostream>
#include <stdlib.h>
using namespace std;

class Singleton
{
public:
    static Singleton * getInstance()
    {
        if(_pInstance==nullptr){
            _pInstance=new Singleton();
            atexit(destroy);
        }
        return _pInstance;
    }

    void print() const {    cout<<"print()"<<endl;  }

    static void destroy()
    {
        if(_pInstance)
            delete _pInstance;
    }

private:
    Singleton() {   cout<<"Singleton()"<<endl;  }
    ~Singleton() {  cout<<"~Singleton()"<<endl; }
    static Singleton * _pInstance;
};

//Singleton * Singleton::_pInstance = nullptr;//饿汉模式
Singleton * Singleton::_pInstance = getInstance();

int main()
{
    Singleton * p = Singleton::getInstance();
    p->print();

    return 0;
}

