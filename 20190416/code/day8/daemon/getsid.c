#include <func.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(!pid)
	{
		printf("child pid=%d,ppid=%d,pgid=%d,sid=%d\n",getpid(),getppid(),getpgid(0),getsid(0));
		while(1);
	}else{
		printf("parent pid=%d,ppid=%d,pgid=%d,sid=%d\n",getpid(),getppid(),getpgid(0),getsid(0));
		while(1);
	}
}

