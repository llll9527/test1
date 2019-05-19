#include <func.h>

void* thFunc(void *p)
{
	printf("I am child thread %ld\n",(long)p);
	pthread_exit((void *)2);
}
int main()
{
	pthread_t pthID;
	int ret;
	long num;
	ret=pthread_create(&pthID,NULL,thFunc,(void*)1);
	THREAD_ERROR_CHECK(ret,"pthread_create");
	ret=pthread_join(pthID,(void**)&num);
	THREAD_ERROR_CHECK(ret,"pthread_join");
	printf("I am main thread %ld\n",num);
	return 0;
}
