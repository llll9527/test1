#include <func.h>
#define N 10000000
int main()
{
	int shmid;
	shmid=shmget(1000,4096,0600|IPC_CREAT);
	ERROR_CHECK(shmid,-1,"shmget");
	int *p;
	p=(int*)shmat(shmid,NULL,0);
	ERROR_CHECK(p,(int*)-1,"shmat");
	p[0]=0;
	int semID;
	semID=semget(1000,1,IPC_CREAT|0600);
	ERROR_CHECK(semID,-1,"semget");
	int ret;
	ret=semctl(semID,0,SETVAL,1);
	ERROR_CHECK(ret,-1,"semctl");
	int i;
	struct sembuf sopp,sopv;
	sopp.sem_num=0;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	sopv.sem_num=0;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;
	if(!fork()){
		for(i=0;i<N;i++){
			semop(semID,&sopp,1);
			p[0]+=1;
			semop(semID,&sopv,1);
		}
		return 0;
	}else{
		for(i=0;i<N;i++){
			semop(semID,&sopp,1);
			p[0]+=1;
			semop(semID,&sopv,1);
		}
		wait(NULL);
		printf("sum=%d\n",p[0]);
		shmctl(shmid,IPC_RMID,NULL);
		semctl(semID,0,IPC_RMID);
		return 0;
	}
}
