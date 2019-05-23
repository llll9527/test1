#include <iostream>
using namespace std;

class knight
{
public:
    knight(const int number, const int health, int & total)
    : _number(number)
    , _health(health)
    {
        total-=health;
    }
private:
    int _number;
    int _health;
};

class dragon
:public knight
{
public:
    dragon(const int number, const int health, int & total)
    : knight(number,health,total)
    , _weapon(number%3)
    , _morale((total-health)/health)
    {
        total-=health;
    }

private:
    int _weapon;
    double _morale;
};

class ninja
:public knight
{
public:
    ninja(const int number, const int health, int & total)
    : knight(number,health,total)
    , _weapon1(number%3)
    , _weapon2((number+1)%3)
    {
        total-=health;
    }

private:
    int _weapon1;
    int _weapon2;
};

class icemen
:public knight
{
public:
    icemen(const int number, const int health, int & total)
    : knight(number,health,total)
    , _weapon(number%3)
    {
        total-=health;
    }

private:
    int _weapon;
};

class lion
:public knight
{
public:
    lion(const int number, const int health, int & total)
    : knight(number,health,total)
    , _loyal(total-health)
    {
        total-=health;
    }

private:
    int _loyal;
};

class wolf
:public knight
{
public:
    wolf(const int number, const int health, int & total)
    : knight(number,health,total)
    {
        total-=health;
    }

};

int main()
{
    return 0;
}

