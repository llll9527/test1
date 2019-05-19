#include <iostream>
using namespace std;
class Queue
{
public:
    Queue(int num)
    : _que(new int[num]())
    , _front(0)
    , _back(0)
    {
        cout<<"Queue(int)"<<endl;
    }
    void push(int i)
    {
        //cout<<_back<<endl;
        _que[_back]=i;
        _back=(_back+1)%10;
    }
    void pop()
    {
        _front++;
    }
    int front()
    {
        //cout<<_front<<endl;
        return _que[_front];
    }
    int back()
    {
        return _que[(_back+9)%10];
    }
    bool full()
    {
        if(_back+1==_front)
            return true;
        else return false;
    }
    bool empty()
    {
        if(_back==_front)
            return true;
        else return false;
    }
    ~Queue()
    {
        delete [] _que;
        cout<<"~Queue()"<<endl;
    }
private:
    int * _que;
    int _front;
    int _back;
};
int main()
{
    Queue q(10);
    if(!q.full()) q.push(10);
    if(!q.full()) q.push(12);
    if(!q.full()) q.push(14);
    cout<<q.front()<<endl;
    cout<<q.back()<<endl;
    if(!q.empty()) q.pop();
    if(!q.full()) q.push(16);
    cout<<q.front()<<endl;
    cout<<q.back()<<endl;
    return 0;
}

