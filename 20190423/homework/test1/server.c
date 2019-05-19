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
	ret=bind(sFd,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"bind");
	listen(sFd,10);
	int new_fd;
	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	int addrlen=sizeof(client);
	char buf[128]={0};
	fd_set rdset;
	fd_set needSet;
	FD_ZERO(&needSet);
	FD_SET(STDIN_FILENO,&needSet);
	FD_SET(sFd,&needSet);
	while(1)
	{
		memcpy(&rdset,&needSet,sizeof(fd_set));
		ret=select(11,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(sFd,&rdset))
		{
			new_fd=accept(sFd,(struct sockaddr*)&client,&addrlen);
			ERROR_CHECK(new_fd,-1,"accept");
			printf("client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
		FD_SET(new_fd,&needSet);
		}
		if(FD_ISSET(new_fd,&rdset))
		{
			bzero(buf,sizeof(buf));
			ret=recv(new_fd,buf,sizeof(buf),0);
			ERROR_CHECK(ret,-1,"recv");
			if(0==ret)
			{
				printf("byebye\n");
				FD_CLR(new_fd,&needSet);
				close(new_fd);
				continue;
			}
			printf("%s\n",buf);
		}
		if(FD_ISSET(STDIN_FILENO,&rdset))
		{
			memset(buf,0,sizeof(buf));
			ret=read(STDIN_FILENO,buf,sizeof(buf));
			if(0==ret)
			{
				printf("byebye\n");
				break;
			}
			ret=send(new_fd,buf,strlen(buf)-1,0);
			ERROR_CHECK(ret,-1,"send");
		}
	}
	close(sFd);
	return 0;
}
