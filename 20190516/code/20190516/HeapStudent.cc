 ///
 /// @file    Student.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-16 10:10:18
 ///

#include <string.h>
#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;


class Student
{
public:
	Student(const char * name, int id)
	: _name(new char[strlen(name) + 1]()) //new char[](),  加上小括号会初始化；不加，不一定会清0
	, _id(id)
	{
		cout << "Student(const char *, int)" << endl;
		strcpy(_name, name);
	}

	void print() const
	{
		cout << "name: " << _name << endl
			 << "id: " << _id << endl;
	}

	void destroy()
	{
		//this->~Student();//不能达到回收对象的目标
		delete this;
	}

private://无法在类之外调用
	~Student()
	{
		delete [] _name;
		cout << "~Student()" << endl;
	}

public:

	//重载操作
	void * operator new(size_t sz)
#if 1
	{	//自定义开辟空间的方式
		cout << "void * operator new(size_t) " << endl;
		void * ret = malloc(sz);	
		return ret;
	}
#endif

	void operator delete(void * ret)
#if 1
	{	
		cout << "void operator delete(void*) " << endl;
		free(ret);
	}
#endif

private:
	char * _name;
	int _id;
};

//Student stu2("John", 102);//error
 
int main(void)
{
	Student * pstu = new Student("Mike", 100);//ok
	pstu->print();

	pstu->destroy();

	//delete pstu;//error
	//cout << endl;

	//Student stu("Mary", 101);//error


 
	return 0;
}
