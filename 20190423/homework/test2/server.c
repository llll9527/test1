#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int sFd;
	sFd=socket(AF_INET,SOCK_DGRAM,0);
	ERROR_CHECK(sFd,-1,"socket");
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=bind(sFd,(struct sockaddr*)&ser,sizeof(ser));
	ERROR_CHECK(ret,-1,"bind");
	char buf[128]={0};
	struct sockaddr_in client;
	int addrlen=sizeof(client);
	ret=recvfrom(sFd,buf,1,0,(struct sockaddr*)&client,&addrlen);
	ERROR_CHECK(ret,-1,"recvform");
	printf("client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
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
			ret=recvfrom(sFd,buf,sizeof(buf),0,(struct sockaddr*)&client,&addrlen);
			ERROR_CHECK(ret,-1,"recvfrom");
			if(0==ret)
			{
				printf("byebye\n");
				break;
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
			ret=sendto(sFd,buf,strlen(buf)-1,0,(struct sockaddr*)&client,sizeof(client));
			ERROR_CHECK(ret,-1,"sendto");
		}
	}
	close(sFd);
	return 0;
}
