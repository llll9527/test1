#include <func.h>

int main()
{
	int fds[2]={0};
	pipe(fds);
	char buf[30]={0};
	if(!fork()){
		close(fds[0]);
		write(fds[1],"Hello",6);
	}else{
		close(fds[1]);
		read(fds[0],buf,sizeof(buf));
		puts(buf);
		wait(NULL);
		return 0;
	}
}
