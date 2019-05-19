#include <func.h>

void sigFunc1(int signum)
{
	time_t now;
	now=time(NULL);
	printf("真实计时器：%s",ctime(&now));
}
void sigFunc2(int signum)
{
	time_t now;
	now=time(NULL);
	printf("虚拟计时器：%s",ctime(&now));
}
void sigFunc3(int signum)
{
	time_t now;
	now=time(NULL);
	printf("实用计时器：%s",ctime(&now));
}
int main()
{
	signal(SIGALRM,sigFunc1);
	signal(SIGVTALRM,sigFunc2);
	signal(SIGPROF,sigFunc3);
	struct itimerval t1,t2,t3;
	bzero(&t1,sizeof(t1));
	bzero(&t2,sizeof(t2));
	bzero(&t3,sizeof(t3));
	t1.it_value.tv_sec=3;
	t1.it_interval.tv_sec=2;
	t2.it_value.tv_sec=3;
	t2.it_interval.tv_sec=2;
	t3.it_value.tv_sec=3;
	t3.it_interval.tv_sec=2;
	int ret;
	sigFunc1(0);
	sigFunc2(0);
	sigFunc3(0);
	ret=setitimer(ITIMER_REAL,&t1,NULL);
	ERROR_CHECK(ret,-1,"setitimer");
	ret=setitimer(ITIMER_VIRTUAL,&t2,NULL);
	ERROR_CHECK(ret,-1,"setitimer");
	ret=setitimer(ITIMER_PROF,&t3,NULL);
	ERROR_CHECK(ret,-1,"setitimer");
	sleep(5);
	printf("wake!\n");
	while(1);
}
