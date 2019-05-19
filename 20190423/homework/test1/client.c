#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int sFd;
	sFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(sFd,-1,"socket");
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=connect(sFd,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"connect");
	printf("connect success\n");
	char buf[128]={0};
	fd_set rdset;
	while(1)
	{
		FD_ZERO(&rdset);
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(sFd,&rdset);
		ret=select(sFd+1,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(sFd,&rdset))
		{
			bzero(buf,sizeof(buf));
			ret=recv(sFd,buf,sizeof(buf),0);
			ERROR_CHECK(ret,-1,"recv");
			if(0==ret)
			{
				printf("byebye\n");
				break;
			}
			printf("%s\n",buf);
		}
		if(FD_ISSET(STDIN_FILENO,&rdset))
		{
			memset(buf,0,sizeof(0));
			ret=read(STDIN_FILENO,buf,sizeof(buf));
			if(0==ret)
			{
				printf("byebye\n");
				break;
			}
			ret=send(sFd,buf,strlen(buf)-1,0);
			ERROR_CHECK(ret,-1,"send");
		}
	}
	close(sFd);
	return 0;
}
