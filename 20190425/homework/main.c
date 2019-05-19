#include "function.h"
int exitFds[2];
void sigFunc(int signum)
{
    write(exitFds[1],&signum,1);
}
int main(int argc,char* argv[])
{
	while(fork())//创建父进程
    {
        int status;
        wait(&status);
        if(WIFEXITED(status))
        {
            printf("child exit normal\n");
            exit(0);//爷爷经常正常退出
        }
    }
    ARGS_CHECK(argc,4);
    pipe(exitFds);
    signal(SIGUSR1,sigFunc);
	int childNum=atoi(argv[3]);
	Process_Data *pChild=(Process_Data*)calloc(childNum,sizeof(Process_Data));
	makeChild(pChild,childNum);
	int socketFd;
	tcpInit(&socketFd,argv[1],argv[2]);
	int epfd;
	epfd=epoll_create(1);
	struct epoll_event event,*evs;
	evs=(struct epoll_event*)calloc(childNum+2,sizeof(struct epoll_event));//分配空间并初始化
	event.events=EPOLLIN;
	event.data.fd=socketFd;
	int ret;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
	ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=exitFds[0];
    epoll_ctl(epfd,EPOLL_CTL_ADD,exitFds[0],&event);
	int i;
	for(i=0;i<childNum;i++)
	{
		event.data.fd=pChild[i].fd;
		ret=epoll_ctl(epfd,EPOLL_CTL_ADD,pChild[i].fd,&event);
		ERROR_CHECK(ret,-1,"epoll_ctl");
	}
	int readyFdNum;
	int newFd;
	int j;
	while(1)
	{
		readyFdNum=epoll_wait(epfd,evs,childNum+2,-1);
		for(i=0;i<readyFdNum;i++)
		{
			if(evs[i].events==EPOLLIN&&evs[i].data.fd==socketFd)
			{
				newFd=accept(socketFd,NULL,NULL);
				for(j=0;j<childNum;j++)
				{
					if(!pChild[j].busy)
					{
						sendFd(pChild[j].fd,newFd,1);
						pChild[j].busy=1;
						printf("%d child is busy\n",pChild[j].pid);
						break;
					}
				}
				close(newFd);
			}
            if(evs[i].data.fd==exitFds[0])
            {
                printf("start exit\n");
                close(socketFd);
                for(j=0;j<childNum;j++)
                {
                    sendFd(pChild[j].fd,0,0);
                }
                for(j=0;j<childNum;j++)
                {
                    wait(NULL);
                }
                return 0;//父进程正常结束
            }
			for(j=0;j<childNum;j++)
			{
				if(evs[i].data.fd==pChild[j].fd)
				{
					read(pChild[j].fd,&ret,1);
					pChild[j].busy=0;
					printf("%d child is not busy\n",pChild[j].pid);
				}
			}
		}
	}
}
