 ///
 /// @file    Queue.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-17 11:02:24
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Queue
{
public:
	Queue(int size = 10)
	: _size(size)
	, _front(0)
	, _rear(0)
	, _data(new int[_size]())
	{}

	bool empty() const
	{	return _front == _rear;	}

	bool full() const
	{	return _front == (_rear + 1) % _size;	}

	int front() const {	return _data[_front];	}
	int back() const {	return _data[(_rear - 1 + _size) % _size];	}

	void push(const int & number);
	void pop();

private:
	int _size;
	int _front;
	int _rear;
	int * _data;
};

void Queue::push(const int & number)
{
	if(!full()) {
		_data[_rear++] = number;
		_rear %= _size;
	} else {
		cout << "queue is full, cannot push any more data!" << endl;
	}
}

void Queue::pop()
{
	if(!empty()) {
		++_front;
		_front %= _size;
	} else {
		cout << "queue is empty, no more any data!" << endl;
	}
}
 
int main(void)
{
	Queue que;
	cout << "此时队列是否为空? " << que.empty() << endl;
	que.push(1);
	cout << "此时队列是否为空? " << que.empty() << endl;
	
	for(int idx = 2; idx != 12; ++idx) {
		que.push(idx);
	}
	cout << "此时队列是否已满? " << que.full() << endl;

	cout << ">> 队列头部的元素是: " << que.front() << endl;
	cout << ">> 队列尾部的元素是: " << que.back() << endl;
	cout << "执行元素出队和入队操作之后:" << endl;

	que.pop();
	que.push(10);
	cout << ">> 队列头部的元素是: " << que.front() << endl;
	cout << ">> 队列尾部的元素是: " << que.back() << endl;

	while(!que.empty()) {
		cout << que.front() << " ";
		que.pop();
	}
	cout << endl;
	cout << "此时队列是否为空? " << que.empty() << endl;
	return 0;
}
