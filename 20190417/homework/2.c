#include <func.h>

#define ERR_EXIT(m) \
	do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}\
while (0);\

void creat_daemon(void); 
int main(void)
{
	creat_daemon();
	while(1){
		FILE *fd = fopen("/tmp/log","ab+");
		if(fd == NULL)
			ERR_EXIT("open error");
		char buf[128]={0};
		strcpy(buf,"I have run 5s.\n");
		fputs(buf,fd);
		sleep(5);
		fclose(fd);
	}
	return 0;
}
void creat_daemon(void)
{
	pid_t pid;
	pid = fork();
	if( pid == -1)
		ERR_EXIT("fork error");
	if(pid > 0 )
		exit(EXIT_SUCCESS);
	if(setsid() == -1)
		ERR_EXIT("SETSID ERROR");
	chdir("/");
	umask(0);
	return;
}
