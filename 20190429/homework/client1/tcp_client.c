#include "func.h"

int recvCycle(int,char*,int);
int main(int argc,char* argv[])
{
    args_check(argc,3);
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serAddr;
    memset(&serAddr,0,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(argv[2]));
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    ret=connect(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret,-1,"connect");
    char buf[1000]={0};;
    int datalen;
    //----------
    recvCycle(socketFd,(char*)&datalen,sizeof(int));
    recvCycle(socketFd,buf,datalen);
    //----------------------
    off_t downLoadSize,fileSize,beforeSize,fileSlice;
    recvCycle(socketFd,(char*)&datalen,sizeof(int));
    recvCycle(socketFd,(char*)&fileSize,datalen);
    printf("filesize=%ld\n",fileSize);
    //-----------
    int fd;
    fd=open(buf,O_CREAT|O_RDWR,0666);
    ERROR_CHECK(fd,-1,"open");
    fileSlice=fileSize/100;
    beforeSize=downLoadSize=0;
    // struct timeval start,end;
    // gettimeofday(&start,NULL);
    ftruncate(fd,fileSize);
    char *pMap=mmap(NULL,fileSize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ret=recvCycle(socketFd,pMap,fileSize);
    if(-1==ret)
    {
        return-1;
    }
    munmap(pMap,fileSize);
    //------
    recvCycle(socketFd,(char*)&datalen,sizeof(int));
    close(fd);
    close(socketFd);
}
