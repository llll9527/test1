#include <func.h>
#define N 10000000
int main()
{
	int shmid;
	shmid=shmget(1000,4096,IPC_CREAT|0600);
	ERROR_CHECK(shmid,-1,"shmget");
	int *pShm;
	pShm=(int*)shmat(shmid,NULL,0);
	ERROR_CHECK(pShm,(int*)-1,"shmat");
	pShm[0]=0;
	int i;
	int semid=semget(1000,1,IPC_CREAT|0600);
	struct sembuf semp;
	struct sembuf semv;
	semp.sem_num=0;
	semp.sem_op=-1;
	semp.sem_flg=0;
	semv.sem_op=0;
	semv.sem_num=1;
	semv.sem_flg=0;
	if(!fork())
	{
		for(i=0;i<N;i++)
		{
			semop(semid,&semp,1);
			pShm[0]=pShm[0]+1;
			semop(semid,&semp,0);
		}
		return 0;
	}else{
		for(i=0;i<N;i++)
		{
			semop(semid,&semv,0);
			pShm[0]=pShm[0]+1;
			semop(semid,&semv,1);
		}
		wait(NULL);
		printf("result=%d\n",pShm[0]);
		return 0;
	}
}
