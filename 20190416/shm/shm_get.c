#include <func.h>

int main()
{
	int id;
	id=shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(id,-1,"shmget");
	char *p;
	p=(char*)shmat(id,NULL,0);
	printf("%s\n",p);
	return 0;
}
