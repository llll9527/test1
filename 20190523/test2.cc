#include <iostream>
#include <math.h>
using namespace std;

class Circle
{
public:
    Circle()
    : _r(0)
    {}
    
    Circle(double r)
    : _r(r)
    {}
    
    double getArea()
    {
        return _r*_r*3.1415;
    }

    double getPerimeter()
    {
        return 2*_r*3.1415;
    }

    void show()
    {
        cout<<"圆的半径："<<_r<<endl
            <<"圆的面积："<<getArea()<<endl
            <<"圆的周长："<<getPerimeter()<<endl;
    }
private:
    double _r;
};

class Cylinder
:public Circle
{
public:
    Cylinder(double r,double h)
    : Circle(r)
    , _high(h)
    {}

    double getVolume()
    {
        return getArea()*_high;
    }

    void showVolume()
    {
        cout<<"圆柱体的体积："<<getVolume()<<endl;
    }
private:
    double _high;
};
int main()
{
    Cylinder c1(2,2);
    c1.show();
    c1.showVolume();

    return 0;
}

