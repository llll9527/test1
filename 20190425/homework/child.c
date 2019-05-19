#include "function.h"

int makeChild(Process_Data *pChild,int childNum)
{
    int i;
    pid_t pid;
    int fds[2];//与父进程通信的管道
    int ret;
    for(i=0;i<childNum;i++)
    {
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(0==pid)
        {
            close(fds[1]);
            childHandle(fds[0]);
        }
        close(fds[0]);
        pChild[i].pid=pid;
        pChild[i].fd=fds[1];
        pChild[i].busy=0;
    }
    return 0;
}
int childHandle(int fd)
{
    int newFd;
    int exitFlag;
    while(1)
    {
        recvFd(fd,&newFd,&exitFlag);//newFd是传数据给客户端的文件描述符，每次完成任务会卡在这里
        if(exitFlag)
        {
            tranFile(newFd);//fd是与父进程通信的文件描述符
            close(newFd);
        }else{
            exit(0);//保证了子程序完成下载任务后，才会被结束
        }
        write(fd,&newFd,1);
    }
}

