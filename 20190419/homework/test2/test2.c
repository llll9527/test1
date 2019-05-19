#include <func.h>
void cleanup(void *p)
{
	printf("I am cleanup\n");
	free(p);
}
void* thFunc(void *p)
{
	p=(char*)malloc(20);
	pthread_cleanup_push(cleanup,p);
	read(STDIN_FILENO,p,sizeof(p));
	pthread_exit((void *)2);
	pthread_cleanup_pop(1);
}
int main()
{
	pthread_t pthID;
	int ret;
	long num;
	ret=pthread_create(&pthID,NULL,thFunc,(void*)1);
	THREAD_ERROR_CHECK(ret,"pthread_create");
	ret=pthread_cancel(pthID);
	THREAD_ERROR_CHECK(ret,"pthread_cancel");
	ret=pthread_join(pthID,(void**)&num);
	THREAD_ERROR_CHECK(ret,"pthread_join");
	printf("I am main thread %ld\n",num);
	return 0;
}
