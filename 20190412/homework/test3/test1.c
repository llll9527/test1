#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int fdr,fdw;
	fdr=open(argv[1],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");
	fdw=open(argv[2],O_WRONLY);
	ERROR_CHECK(fdw,-1,"open");
	char buf[128]={0};
	fd_set rdset;
	int ret;
	printf("chat1:begin\n");
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(fdr,&rdset);
		ret=select(fdr+1,&rdset,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(fdr,&rdset))
			{
				memset(buf,0,sizeof(buf));
				read(fdr,buf,sizeof(buf));//从管道输入到buf
				printf("%s\n",buf);//输出到屏幕
			}
			if(FD_ISSET(0,&rdset))
			{
				memset(buf,0,sizeof(buf));
				read(0,buf,sizeof(buf));//从键盘输入到buf
				write(fdw,buf,strlen(buf)-1);//输出到管道
			}
		}
	}
	return 0;
}
