#include <iostream>
#include <pthread.h>
using namespace std;
class MutexLock
{
public:
    MutexLock()
    {
        pthread_mutex_init(&_mutex,NULL);
    }
    void lock()
    {
        pthread_mutex_lock(&_mutex);
    }
    void unlock()
    {
        pthread_mutex_unlock(&_mutex);
    }
    pthread_mutex_t _mutex;
};
class Condition
{
public:
    Condition()
    :_mutexLock()
    {
        pthread_cond_init(&_cond,NULL);
    }
    void wait()
    {
        _mutexLock.lock();
        pthread_cond_wait(&_cond,&_mutexLock._mutex);
        _mutexLock.unlock();
    }
    void notify()
    {
        pthread_cond_signal(&_cond);
    }
    void notifyall()
    {
        pthread_cond_broadcast(&_cond);
    }
private:
    pthread_cond_t _cond;
    MutexLock _mutexLock;
};
int main()
{
    return 0;
}

