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
int main()
{
    Circle c1;
    Circle c2(2);
    c1.show();
    c2.show();
    return 0;
}

