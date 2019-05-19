#include <func.h>

void Daemon()
{
	setsid();
	chdir("/");
	umask(0);
}
int main()
{
	if(fork()){
		sleep(20);
		exit(0);
	}
	Daemon();
	int fd;
	char buf[128]={0};
	fd = open("/tmp/log",O_WRONLY|O_CREAT|O_APPEND,0644);
	while(1){
		write(fd,buf,strlen(buf));
		sleep(5);
	}
	return 0;
}
