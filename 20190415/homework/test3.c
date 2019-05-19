#include <func.h>

int main()
{
	pid_t pid;
	char *p=(char*)malloc(20);
	strcpy(p,"hello");
	pid=fork();
	if(0==pid){
		printf("child process,pid:%d\n",getpid());
		printf("%s\n",p);
	}
	else{
		printf("parent process,pid:%d\n",getpid());
		printf("%s\n",p);
		strcpy(p,"world");
		printf("%s\n",p);
		sleep(1);
	}
	return 0;
}
