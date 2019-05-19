#include "function.h"

int tranFile(int newFd)
{
	Train_t train;
    int ret;
    //---------------
	train.dataLen=strlen(FILENAME);
	strcpy(train.buf,FILENAME);
	ret=send(newFd,&train,4+train.dataLen,0);
    ERROR_CHECK(ret,-1,"send");
	int fd=open(FILENAME,O_RDONLY);
	ERROR_CHECK(fd,-1,"open");
    //----------------------
    struct stat buf;
    fstat(fd,&buf);
    train.dataLen=sizeof(buf.st_size);
    memcpy(train.buf,&buf.st_size,train.dataLen);
    ret=send(newFd,&train,4+train.dataLen,0);
    ERROR_CHECK(ret,-1,"send");
    //------------------
	while((train.dataLen=read(fd,train.buf,sizeof(train.buf))))
	{
		ret=send(newFd,&train,4+train.dataLen,0);
        ERROR_CHECK(ret,-1,"send");
	}
	ret=send(newFd,&train,4,0);
    ERROR_CHECK(ret,-1,"send");
	return 0;
}
