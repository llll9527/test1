#include <iostream>
#include <string.h>
using namespace std;

class String
{
public:
    String();//构造
    String(const char * pstr);//构造
    String(const String &rhs)//构造
    : _pstr(new char[strlen(rhs._pstr)+1]())
    {
        cout<<"String(const String&)"<<endl;
        strcpy(_pstr,rhs._pstr);
    }
    //String & operator=(const String & rhs)//复制构造函数
    //{
    //    cout<<"String & operator=(const String &)"<<endl;
    //    if(this != &rhs){
    //        delete [] _pstr;
    //        _pstr=new char[strlen(rhs._pstr)+1]();
    //        strcpy(_pstr,rhs._pstr);
    //    }
    //    return *this;
    //}
    ~String()//析构函数
    {
        delete [] _pstr;
        cout<<"~String()"<<endl;
    }
    void print()
    {
        printf("%s\n",_pstr);
    }
private:
    char * _pstr;
};

String::String(const char * pstr)
:_pstr(new char[strlen(pstr)+1]())
{
    cout<<"String(const char *)"<<endl;
    strcpy(_pstr,pstr);
}
String::String()
: _pstr(new char)
{
    *_pstr='\0';
    cout<<"String()"<<endl;
}
int main(void)
{
    String str1;
    str1.print();

    String str2="Hello,world";
    String str3("wangdao");

    str2.print();
    str3.print();

    String str4=str3;
    str4.print();

    str4=str2;
    str4.print();

    return 0;
}
