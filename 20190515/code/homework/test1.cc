#include <iostream>
using namespace std;
class Stack
{
public:
    Stack(int num)
    : _sta(new int[num]())
    , _count(0)
    {
        cout<<"Stack(int)"<<endl;
    }
    void push(int i)
    {
        _sta[_count++]=i;
    }
    void pop()
    {
        _count--;
    }
    int top()
    {
        return _sta[_count-1];
    }
    bool empty()
    {
        if(_count==0)
            return true;
        else return false;
    }
    bool full()
    {
        if(_count==10)
            return true;
        else return false;
    }
    ~Stack()
    {
        delete [] _sta;
        cout<<"~Stack()"<<endl;
    }
private:
    int * _sta;
    int _count;
};
int main()
{
    Stack s(10);
    if(!s.full()) s.push(10);
    if(!s.full()) s.push(12);
    if(!s.full()) s.push(14);
    cout<<s.top()<<endl;
    if(!s.empty()) s.pop();
    cout<<s.top()<<endl;
    return 0;
}

