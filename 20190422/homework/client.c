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
	ret=send(sFd,"hello",5,0);
	ERROR_CHECK(ret,-1,"send");
	char buf[128]={0};
	ret=recv(sFd,buf,sizeof(buf),0);
	ERROR_CHECK(ret,-1,"recv");
	printf("I am client,gets %s\n",buf);
	close(sFd);
	return 0;
}
