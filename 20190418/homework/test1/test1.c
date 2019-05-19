#include <func.h>

void sigFunc(int signum){
	printf("before: %d is coming\n",signum);
	sleep(3);
	printf("after: %d is coming\n",signum);
}

int main()
{
	signal(SIGINT,sigFunc);
	signal(SIGQUIT,sigFunc);
	while(1);
}
