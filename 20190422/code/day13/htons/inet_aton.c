#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	struct in_addr addr;
	int ret;
	ret=inet_aton(argv[1],&addr);//点分转网络
	printf("%x\n",addr.s_addr);
	printf("ip=%s\n",inet_ntoa(addr));//网络转点分
	printf("%x\n",inet_addr(argv[1]));//点分转网络
	return 0;
}
