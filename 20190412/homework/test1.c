#include <func.h>

struct student{
	int num;
	float score;
}s[3]={{1001,85.5},{1002,92.5},{1003,95.5}};
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	write(fd,s,sizeof(s));
	ERROR_CHECK(fd,-1,"write");
	lseek(fd,0,SEEK_SET);
	memset(s,0,sizeof(s));
	read(fd,s,sizeof(s));
	ERROR_CHECK(fd,-1,"read");
	for(int i=0;i<3;i++){
		printf("学号：%d 成绩：%f\n",s[i].num,s[i].score);
	}
	return 0;
}
