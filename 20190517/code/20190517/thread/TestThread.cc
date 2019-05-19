 ///
 /// @file    TestThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-17 11:49:17
 ///
 
#include "MutexLock.h"
#include "Condition.h"
#include <iostream>
using std::cout;
using std::endl;



int gTicket = 100;
bool flag = true;
wd::MutexLock mutex;//系统资源 不能进行复制
wd::Condition condition(mutex);

//wd::MutexLock mutex2(mutex);//error  调用复制构造函数

void * threadFunc1(void * arg)
{	//flag 为true时，执行减1的操作
	int cnt = 20;
	while(cnt--) {
		{
		wd::MutexLockGuard autolock(mutex);//防止死锁
		if(false == flag) {
			condition.wait();
		}

		--gTicket;
		cout << "sub thread " << pthread_self() << ":"
			 << " gTicket = " << gTicket << endl;
		if(flag)
			flag = false;
		}
		condition.notify();
	}
	return NULL;
}


void * threadFunc2(void * arg)
{	//flag 为false时，执行减1的操作
	int cnt = 20;
	while(cnt--) {
		{
		wd::MutexLockGuard autolock(mutex);//防止死锁
		if(true == flag) {
			condition.wait();
		}

		--gTicket;
		cout << "sub thread " << pthread_self() << ":"
			 << " gTicket = " << gTicket << endl;
		if(flag == false) {
			flag = true;
		}
		}// 可以通过语句块来减小加锁的范围, 从而控制临界资源的区域
		condition.notify();
	}
	return NULL;
}

 
int main(void)
{
	pthread_t pthid1, pthid2;
	pthread_create(&pthid1, NULL, threadFunc1, NULL);
	pthread_create(&pthid2, NULL, threadFunc2, NULL);

	pthread_join(pthid1, NULL);
	pthread_join(pthid2, NULL);

	wd::MutexLock mutex3;
	mutex3 = mutex;//error 

	return 0;
}
