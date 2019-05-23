#include <iostream>
#include <string.h>
using namespace std;

class person
{
public:
    person(const char * name, const int age)
    : _name(new char[strlen(name)+1]())
    , _age(age)
    {
        strcpy(_name,name);
    }

    void display()
    {
        cout<<"name: "<<_name<<endl
            <<"age: "<<_age<<endl;
    }
private:
    char * _name;
    int _age;
};

class employee
:public person
{
public:
    employee(const char * name, const int age, const char * department, const double salary)
    : person(name,age)
    , _department(new char[strlen(department)+1]())
    , _salary(salary)
    {
        strcpy(_department,department);
    }

    void display()
    {
        person::display();
        cout<<"department: "<<_department<<endl
            <<"salary: "<<_salary<<endl;
    }

    double getSalary()
    {
        return _salary;
    }

private:
    char * _department;
    double _salary;
};
int main()
{
    employee e1("xiongda",20,"dongwu",2000);
    employee e2("xionger",19,"dongwu",1900);
    employee e3("guangtouqiang",21,"famu",2100);
    e1.display();
    e2.display();
    e3.display();
    cout<<"average salary: "<<(e1.getSalary()+e2.getSalary()+e3.getSalary())/3<<endl;
    return 0;
}

