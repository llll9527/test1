#include <func.h>

int main()
{
	char buf[32];
	int fd1,fd2;
	fd1=dup(stdin);
	fd2=dup(stdout);
	printf("input:");
	fgets(buf,sizeof(buf),fd1);
	fprintf(stdout,"The string is:%s",fd2);
	return 0;
}
