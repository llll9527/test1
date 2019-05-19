#include <func.h>

int main ()
{
	pid_t i=fork();
	if(i==0){
		printf("child process pid:%d\n",getpid());
		while(1);
	}
	else{
		printf("parent process pid:%d\n",getpid());
		while(1);
	}
	return 0;
}
