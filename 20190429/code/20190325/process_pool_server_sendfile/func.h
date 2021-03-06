#include <sys/sendfile.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <sys/msg.h>
#include <strings.h>
#include <syslog.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#define args_check(argc,num) {if(argc!=num) {printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retval,funcname) {if(ret==retval) {perror(funcname);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcname) {if(ret != 0) {printf("%s failed %s\n",funcname,strerror(ret));return -1;}}

typedef struct{
	pid_t pid;
	int fd;
	short busy;//代表子进程是否忙碌,0代表不忙碌，1代表忙碌
}Process_Data;
//小火车
typedef struct{
	int dataLen;
	char buf[1000];
}train;
int makeChild(Process_Data *p,int processNum);
void childHandle(int);
int tcpInit(int*,char*,char*);
int sendFd(int,int,int);
int recvFd(int,int*,int*);
int tranFile(int);
int sendCycle(int,char*,int);
int recvCycle(int,char*,int);
#define FILENAME "file"
