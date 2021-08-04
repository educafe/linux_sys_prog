#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define KEY_NUM     0x2222
#define	MEM_SIZE	1024

static int	semid;

void lock(){
	int ret;
	struct sembuf lockop;		//set of semaphore *sops
	lockop.sem_num = 0;			//세마포어 번호
	lockop.sem_op = -1;			//세마포어 연산
	lockop.sem_flg = SEM_UNDO;	//프로세스가 종료되면 시스템에서 세마포어 설정을 원래상태로 복귀
	if(semop(semid, &lockop, 1) == -1){
		perror("lock()-semop");
	}
}
void unlock(){
	struct sembuf unlockop;			//set of semaphore *sops
	unlockop.sem_num = 0;			//세마포어 번호
	unlockop.sem_op = 1;			//세마포어 연산
	unlockop.sem_flg = SEM_UNDO;	//프로세스가 종료되면 시스템에서 세마포어 설정을 원래상태로 복귀
	if(semop(semid, &unlockop, 1) == -1){
		perror("unlock()-semop");
	}
}

// union senum {
		// int val;
		// struct semid_ds *buf;
		// unsigned short int *array;
// } sem_ctrl;

int main() {
	int shm_id;
	void *shm_addr;
	int i, j;
	struct shmid_ds shm_stat;
	
	int sem_val;
	
	printf("Started --------------------\n");
	if((shm_id = shmget((key_t)KEY_NUM,MEM_SIZE,IPC_CREAT|0666)) == -1){
		perror("shmget");
		exit(1);
	}

	if((shm_addr = shmat(shm_id, NULL, 0)) == (void *)-1){
		perror("shmat");
		exit(1);
	}
	
	if((semid = semget((key_t)0x1234,1,IPC_CREAT|0666)) == -1){
		perror("shmget");
		exit(1);
	}
	
#if 0
	sem_val=semctl(semid, 0, GETVAL, sem_ctrl);
	printf(" sema:%d\n ", sem_val);
#endif

	for(i=0; i<500; i++) {
#ifdef SEM
		lock();
#endif
		sprintf((char *)shm_addr, "%d", getpid());
		for(j=0; j<5000000; j++){}
		if(getpid() == atoi(shm_addr))
			putchar('0');
		else
			putchar('X');
		fflush(stdout);
#ifdef SEM
		unlock();
#endif
	}
	
	if(shmdt(shm_addr) !=0){
		perror("shmdt");
		exit(2);
	}
	
	// if(shmctl(shm_id, IPC_RMID, NULL) == -1){
		// perror("shmctl");
		// exit(2);
	// }
	
	return 0;
}