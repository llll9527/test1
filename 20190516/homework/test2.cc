#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

class Student
{
public:
    Student(const char * name, int id)
    : _name(new char[strlen(name)+1]())
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
        delete this;
    }

    void * operator new(size_t sz)
    {
        cout << "void * operator new(size_t) " << endl;
        void * ret = malloc(sz);
        return ret;
    }

    void operator delete(void * ret)
    {
        cout << "void operator delete(void *)" << endl;
        free(ret);
    }
private:
    ~Student()
    {
        delete [] _name;
        cout << "~Student()" << endl;
    }
    char * _name;
    int _id;
};

int main()
{
    Student * pstu = new Student("xiongda",2014112047);
    pstu->print();
    pstu->destroy();
    return 0;
}

