#include <func.h>

int main()
{
	sigset_t proc;
	sigemptyset(&proc);
	sigaddset(&proc,SIGINT);
	int ret;
	ret=sigprocmask(SIG_BLOCK,&proc,NULL);
	ERROR_CHECK(ret,-1,"sigprocmask");
	sleep(5);
	printf("important code\n");
	sigset_t pending;
	sigemptyset(&pending);
	sigpending(&pending);
	if(sigismember(&pending,SIGINT))
		printf("SIGINT is pending\n");
	else
		printf("SIGINT is not pending\n");
	sigprocmask(SIG_UNBLOCK,&proc,NULL);
	return 0;
}
