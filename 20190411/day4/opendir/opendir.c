#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	DIR *dir;
	dir=opendir(argv[1]);
	ERROR_CHECK(dir,NULL,"opendir");
	struct dirent *p;
	while(p=readdir(dir))
	{
		printf("%ld %d %d %s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
	}
	closedir(dir);
	return 0;
}
