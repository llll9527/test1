#include <func.h>
#define N 10000000
typedef struct{
	int num;
	pthread_mutex_t mutex;
}Date;
void* thFunc(void *p)
{
	Date *pTh=(Date *)p;
	int i;
	for(i=0;i<N;i++)
	{
		pthread_mutex_lock(&pTh->mutex);
		pTh->num+=1;
		pthread_mutex_unlock(&pTh->mutex);
	}
	printf("child thread\n");
	pthread_exit(NULL);
}

int main()
{
	pthread_t pthID;
	int ret;
	Date th;
	th.num=0;
	ret=pthread_mutex_init(&th.mutex,NULL);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
	ret=pthread_create(&pthID,NULL,thFunc,&th);
	THREAD_ERROR_CHECK(ret,"pthread_create");
	int i;
	for(i=0;i<N;i++)
	{
		pthread_mutex_lock(&th.mutex);
		th.num+=1;
		pthread_mutex_unlock(&th.mutex);
	}
	pthread_join(pthID,NULL);
	ret=pthread_mutex_destroy(&th.mutex);
	THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");
	printf("main thread %d\n",th.num);
	return 0;
}
