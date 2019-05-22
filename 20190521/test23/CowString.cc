#include <iostream>
#include <string.h>
using namespace std;

class CowString
{
    class charProxy
    {
    public:
        charProxy(CowString & str,int index)
        : _str(str)
        , _index(index)
        {
            cout<<"charProxy(CowString &,int)"<<endl;
        }

        char & operator=(const char & ch);
        operator char()
        {
            cout<<"operator char()"<<endl;
            return _str._pstr[_index];
        }
    private:
        CowString & _str;
        int _index;
    };
public:
    CowString();
    CowString(const char * pstr);
    CowString(const CowString & rhs);
    CowString & operator=(const CowString & rhs);
    ~CowString();

    const char * c_str() const {    return _pstr;   }
    int size() const {  return strlen(_pstr);   }
    int refcount() const {    return *((int*)(_pstr-4));  }

    friend ostream & operator<<(ostream & os, const CowString & rhs);
    charProxy operator[](int index);
private:
    void initRefcount() {   *((int*)(_pstr-4))=1;   }
    void increaseRefcount() {   ++*((int*)(_pstr-4));   }
    void decreaseRefcount() {   --*((int*)(_pstr-4));   }
    void release()
    {
        decreaseRefcount();
        if(refcount()==0){
            delete [] (_pstr-4);
            cout<<">>> delete data!"<<endl;
        }
    }
    char * _pstr;
};

CowString::CowString()
    : _pstr(new char[1+4]()+4)
{
    cout<<"CowString()"<<endl;
    initRefcount();
}

CowString::CowString(const char * pstr)
    : _pstr(new char[strlen(pstr)+5]()+4)
{
    initRefcount();
    strcpy(_pstr,pstr);
    cout<<"CowString(const char *)"<<endl;
}

CowString::CowString(const CowString & rhs)
    : _pstr(rhs._pstr)
{
    cout<<"CowString(const CowString &)"<<endl;
    increaseRefcount();
}

CowString & CowString::operator=(const CowString & rhs)
{
    cout<<"CowString & operator=(const CowString &)"<<endl;
    if(this != & rhs){
        release();

        _pstr=rhs._pstr;
        increaseRefcount();
    }
    return *this;
}

CowString::~CowString()
{
    release();
}
#if 0
char & CowString::operator[](int idx)
{
    cout<<"char & operator[](int idx)"<<endl;
    if(idx>=0 && idx<size()){
        if(refcount()>1){
            decreaseRefcount();

            char * ptmp = new char[size()+5]()+4;
            strcpy(ptmp,_pstr);
            _pstr=ptmp;
            initRefcount();
        }
        return _pstr[idx];
    }else{
        cout<<"下标越界！"<<endl;
        static char nullchar = '\0';
        return nullchar;
    }
}
#endif

CowString::charProxy CowString::operator[](int idx)
{
    return charProxy(*this,idx);
}

char & CowString::charProxy::operator=(const char & ch)
{
    int sz = _str.size();
    if(_index >= 0 && _index < sz){
        if(_str.refcount() > 1){
            _str.decreaseRefcount();

            char * ptmp = new char[sz + 5]() + 4;
            strcpy(ptmp, _str._pstr);
            _str._pstr = ptmp;
            _str.initRefcount();
        }
        _str._pstr[_index] = ch;
        return _str._pstr[_index];
    }else{
        cout<<"下标越界!"<<endl;
        static char nullchar = '\0';
        return nullchar;
    }
}

ostream & operator<<(ostream & os, const CowString & rhs)
{
    os<<rhs._pstr;
    return os;
}

int main(void)
{
    CowString s0;
    cout<<"s0 = "<<s0<<endl;
    CowString s1("hello,world");
    CowString s2(s1);

    CowString s3=s2;
    cout<< "s1 = "<<s1<<endl;
    cout<< "s2 = "<<s2<<endl;
    cout<< "s3 = "<<s3<<endl;
    printf("s1's address: %p\n",s1.c_str());
    printf("s2's address: %p\n",s2.c_str());
    printf("s3's address: %p\n",s3.c_str());
    cout<<"s1's refcount() = "<<s1.refcount()<<endl;
    cout<<"s2's refcount() = "<<s2.refcount()<<endl;
    cout<<"s3's refcount() = "<<s3.refcount()<<endl;
    
    cout<<endl<<">>>执行s1[0]='x'之后:"<<endl;
    s1[0]='x';
    cout<< "s1 = "<<s1<<endl;
    cout<< "s2 = "<<s2<<endl;
    cout<< "s3 = "<<s3<<endl;
    printf("s1's address: %p\n",s1.c_str());
    printf("s2's address: %p\n",s2.c_str());
    printf("s3's address: %p\n",s3.c_str());
    cout<<"s1's refcount() = "<<s1.refcount()<<endl;
    cout<<"s2's refcount() = "<<s2.refcount()<<endl;
    cout<<"s3's refcount() = "<<s3.refcount()<<endl;

    cout<<endl<<">>>执行cout <<s2[0]之后:"<<endl;
    cout<< "s2[0] = "<<s2[0]<<endl;
    cout<< "s1 = "<<s1<<endl;
    cout<< "s2 = "<<s2<<endl;
    cout<< "s3 = "<<s3<<endl;
    printf("s1's address: %p\n",s1.c_str());
    printf("s2's address: %p\n",s2.c_str());
    printf("s3's address: %p\n",s3.c_str());
    cout<<"s1's refcount() = "<<s1.refcount()<<endl;
    cout<<"s2's refcount() = "<<s2.refcount()<<endl;
    cout<<"s3's refcount() = "<<s3.refcount()<<endl;
    
    return 0;
}

