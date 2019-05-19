#include <func.h>
int main()
{
	int semID;
	semID=semget(1000,2,IPC_CREAT|0600);
	ERROR_CHECK(semID,-1,"semget");
	int ret;
	unsigned short arr[2]={10,0};
	ret=semctl(semID,0,SETALL,arr);
	ERROR_CHECK(ret,-1,"semctl");
	struct sembuf sopp,sopv;
	if(!fork())
	{
		sopp.sem_num=0;
		sopp.sem_op=-1;
		sopp.sem_flg=SEM_UNDO;
		sopv.sem_num=1;
		sopv.sem_op=1;
		sopv.sem_flg=SEM_UNDO;
		while(1)
		{
			printf("生产者，商品数：%d 仓库空间：%d\n",semctl(semID,1,GETVAL),semctl(semID,0,GETVAL));
			semop(semID,&sopp,1);
			printf("生产商品\n");
			semop(semID,&sopv,1);
			printf("生产者，商品数：%d 仓库空间：%d\n\n",semctl(semID,1,GETVAL),semctl(semID,0,GETVAL));
		sleep(1);
		}
	}else{
		sopp.sem_num=1;
		sopp.sem_op=-1;
		sopp.sem_flg=SEM_UNDO;
		sopv.sem_num=0;
		sopv.sem_op=1;
		sopv.sem_flg=SEM_UNDO;
		while(1){
			printf("消费者，商品数：%d 仓库空间：%d\n",semctl(semID,1,GETVAL),semctl(semID,0,GETVAL));
			semop(semID,&sopp,1);
			printf("消费商品\n");
			semop(semID,&sopv,1);
			printf("消费者，商品数：%d 仓库空间：%d\n\n",semctl(semID,1,GETVAL),semctl(semID,0,GETVAL));
		sleep(2);
		}
	}
	return 0;
}
