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

	~Student()
	{
		delete [] _name;
		cout << "~Student()" << endl;
	}
	
private:
	//重载操作
	void * operator new(size_t sz);
	void operator delete(void * ret);

private:
	char * _name;
	int _id;
};

//一个类只能生成栈对象, 不能生成堆对象
//方案: 将operator new放入private区域
 
int main(void)
{
	Student * pstu = new Student("Mike", 100);//error 编译不通过
	//pstu->print();
	//delete pstu;

	Student stu("Mary", 101);//ok  编译通过
	stu.print();
 
	return 0;
}
