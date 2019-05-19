#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	DIR *dir;
	char name[128]={0};
	dir=opendir(argv[1]);
	ERROR_CHECK(dir,NULL,"opendir");
	struct dirent *p;
	while((p=readdir(dir)))
	{
		if(!strcmp(p->d_name,argv[2]))
		{
			sprintf(name,"%s/%s\n",getcwd(NULL,0),argv[2]);
			printf("%s",name);
			return 0;
		}
	}
	printf("can not such file\n");
	return 0;
}

