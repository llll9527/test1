#include <iostream>
#include <string.h>
using namespace std;

class String
{
public:
    String();
    String(const char *);
    String(const String &);
    ~String();
    
    String &operator=(const String &);
    String &operator=(const char *);
    
    String &operator+=(const String &);
    String &operator+=(const char *);

    char &operator[](size_t index);
    const char &operator[](size_t index) const;

    size_t size() const
    {
        return strlen(_pstr);
    }
    const char* c_str() const
    {
        return _pstr;
    }

    friend bool operator==(const String &,const String &);
    friend bool operator!=(const String &,const String &);

    friend bool operator>(const String &,const String &);
    friend bool operator<(const String &,const String &);
    friend bool operator<=(const String &,const String &);
    friend bool operator>=(const String &,const String &);

    friend ostream &operator<<(ostream &os,const String &s);
    friend istream &operator>>(istream &is,String &s);
private:
    char * _pstr;
};
String operator+(const String &lhs,const String &rhs)
{
    String tmp(lhs);
    tmp+=rhs;
    return tmp;
}

String operator+(const String &lhs,const char *s)
{
    String tmp(lhs);
    tmp+=s;
    return tmp;
}

String operator+(const char *s,const String &rhs)
{
    String tmp(s);
    tmp+=rhs;
    return tmp;
}

String::String()
: _pstr(new char)
{
    *_pstr='\0';
    cout<<"String()"<<endl;
}

String::String(const char * pstr)
: _pstr(new char[strlen(pstr)+1]())
{
    cout<<"String(const char *)"<<endl;
    strcpy(_pstr,pstr);
}

String::String(const String &rhs)
: _pstr(new char[strlen(rhs._pstr)+1]())
{
    cout<<"String(const String&)"<<endl;
    strcpy(_pstr,rhs._pstr);
}

String::~String()
{
    delete [] _pstr;
    cout<<"~String"<<endl;
}

String & String::operator=(const String & rhs)
{
    cout<<"String & operator=(const String &)"<<endl;
    if(this != &rhs){
        delete [] _pstr;
        _pstr=new char[strlen(rhs._pstr)+1]();
        strcpy(_pstr,rhs._pstr);
    }
    return *this;
}

String & String::operator=(const char *s)
{
    cout<<"String & operator=(const char *)"<<endl;
    delete [] _pstr;
    _pstr=new char[strlen(s)+1]();
    strcpy(_pstr,s);
    return *this;
}

String & String::operator+=(const String & rhs)
{
    cout<<"String & operator+=(const String &)"<<endl;
    String tmp(*this);
    delete [] _pstr;
    _pstr=new char[tmp.size()+strlen(rhs._pstr)+1]();
    strcpy(_pstr,tmp._pstr);
    strcat(_pstr,rhs._pstr);
    return *this;
}

String & String::operator+=(const char *s)
{
    cout<<"String & operator+=(const char *)"<<endl;
    String tmp(*this);
    delete [] _pstr;
    _pstr=new char[size()+strlen(s)+1]();
    strcpy(_pstr,tmp._pstr);
    strcat(_pstr,s);
    return *this;
}

char & String::operator[](size_t index)//可读写
{
    if(index<size()){
        return _pstr[index];
    }else{
        static char nullchar = '\0';
        cout<<">> error 下标越界!!"<<endl;
        return nullchar;
    }
}

const char & String::operator[](size_t index) const//只读
{
    if(index<size()){
        return _pstr[index];
    }else{
        static char nullchar = '\0';
        cout<<">> error 下标越界!!"<<endl;
        return nullchar;
    }
}

bool operator==(const String &lhs,const String &rhs)
{
    return !strcmp(lhs._pstr,rhs._pstr);
}

bool operator!=(const String &lhs,const String &rhs)
{
    return strcmp(lhs._pstr,rhs._pstr);
}

bool operator>(const String &lhs,const String &rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr)>0)
        return 1;
    else return 0;
}

bool operator<(const String &lhs,const String &rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr)<0)
        return 1;
    else return 0;
}

bool operator<=(const String &lhs,const String &rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr)<=0)
        return 1;
    else return 0;
}

bool operator>=(const String &lhs,const String &rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr)>=0)
        return 1;
    else return 0;
}

ostream &operator<<(ostream &os,const String &s)
{
    cout<<s._pstr<<endl;
    return os;
}

istream &operator>>(istream &is,String &s)
{
    is>>s._pstr;
    return is;
}

int main()
{
    String s1("hello");
    cout<<"s1 = "<<s1;
    String s2=s1+",world";
    cout<<"s2 = "<<s2;
    cout<<"s2[2] = "<<s2[2]<<endl;
    String s3;
    cin>>s3;
    cout<<"s3 = "<<s3;
    cout<<"s3==s2 ? "<<(s3==s2)<<endl;
    return 0;
}

