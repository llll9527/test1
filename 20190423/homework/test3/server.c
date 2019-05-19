#include <func.h>
void change(int fd)
{
	int status=fcntl(fd,F_GETFL);
	status=status|O_NONBLOCK;
	fcntl(fd,F_SETFL,status);
}
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
	new_fd=accept(sFd,(struct sockaddr*)&client,&addrlen);
	ERROR_CHECK(new_fd,-1,"accept");
	printf("client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	char buf[6]={0};
	int epfd=epoll_create(1);
	ERROR_CHECK(epfd,-1,"epoll_create");
	struct epoll_event event,evs[2];
	event.events=EPOLLIN;
	event.data.fd=STDIN_FILENO;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	ERROR_CHECK(ret,-1,"epoll_ctl");
	event.events=EPOLLIN|EPOLLET;
	change(new_fd);
	event.data.fd=new_fd;
	epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
	int i;
	int ready;
	while(1)
	{
		memset(evs,0,sizeof(evs));
		ready=epoll_wait(epfd,evs,2,-1);
		for(i=0;i<ready;i++)
		{
			if(evs[i].data.fd==new_fd)
			{
				while(1)
				{
					bzero(buf,sizeof(buf));
					ret=recv(new_fd,buf,sizeof(buf)-1,0);
					if(0==ret)
					{
						printf("byebye\n");
						goto FLAG;
					}else if(-1==ret)
					{
						printf("\n");
						break;
					}else{
						printf("%s",buf);
					}
				}
			}
			if(0==evs[i].data.fd)
			{
				memset(buf,0,sizeof(buf));
				ret=read(STDIN_FILENO,buf,sizeof(buf));
				if(0==ret)
				{
					printf("byebye\n");
					goto FLAG;
				}
				ret=send(new_fd,buf,strlen(buf)-1,0);
				ERROR_CHECK(ret,-1,"send");
			}
		}
	}
FLAG:
	close(new_fd);
	close(sFd);
	return 0;
}
