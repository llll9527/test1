#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	DIR *dir;
	dir=opendir(argv[1]);
	ERROR_CHECK(dir,NULL,"opendir");
	struct dirent *p;
	int ret;
	struct stat buf;
	char day[30]={0};
	char num[10]={0};
	char str[8][5]={"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};
	char str1[5]={0};
	char str2[5]={0};
	char str3[5]={0};
	char c;
	while((p=readdir(dir)))
	{
		ret=stat(p->d_name,&buf);
		ERROR_CHECK(ret,-1,"stat");
		memcpy(day,ctime(&buf.st_mtime)+4,15);
	    sprintf(num,"%o",buf.st_mode);
		int i=0;
		if(num[i]=='1'){
			c='-';
			i=i+3;
		}
		else{
			c='d';
			i=i+2;
		}
		strcpy(str1,str[num[i++]-'0']);
		strcpy(str2,str[num[i++]-'0']);
		strcpy(str3,str[num[i++]-'0']);
		printf("%ld %c%s%s%s %ld %s %s %10ld %s %s\n",buf.st_ino,c,str1,str2,str3,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,day,p->d_name);
	}
	return 0;
}
