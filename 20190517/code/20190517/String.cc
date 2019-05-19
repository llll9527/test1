 ///
 /// @file    String.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-17 09:59:57
 ///
 
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class String
{
public:
	String()
	//: _pstr(new char[1]())
	: _pstr(nullptr)
	{
		cout << "Strng()" << endl;
	}

	String(const char * pstr)
	: _pstr(new char[strlen(pstr) + 1]())
	{
		cout << "String(const char * )" << endl;
		strcpy(_pstr, pstr);
	}

	String(const String & rhs)
	: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		cout << "String(const String & rhs )" << endl;
		strcpy(_pstr, rhs._pstr);
	}

	String & operator=(const String & rhs)
	{
		cout << "String & operator=(const String &rhs)" << endl;
		if(this != & rhs) {
			delete [] _pstr;

			_pstr = new char[strlen(rhs._pstr)]();
			strcpy(_pstr, rhs._pstr);
		}
		return *this;
	}

	~String()
	{
		delete [] _pstr;
		cout << "~String()" << endl;
	}

	void print() const
	{
		//int * p = nullptr;
		//cout << p << endl;
		if(_pstr != nullptr) {
			cout << _pstr << endl;//cout不能针对于char*的空指针执行操作
		}
	}

private:
	char * _pstr;
};
 
int main(void)
{
	String s1;
	cout << "0000" << endl;
	s1.print();
	cout << "1111" << endl;
	String s2("hello,world");
	cout << "2222" << endl;
	s2.print();

	String s3 = "wangdao";
	s3 = s2;

	cout << "s3 = ";
	s3.print();

	String s4 = s3;
	cout << "s4 = ";
	s4.print();

 
	return 0;
}
