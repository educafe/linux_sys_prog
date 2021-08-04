#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
	union senum {
		int val;
		struct semid_ds *buf;
		unsigned short int *array;
	} sem_ctrl;
	
	int sem_val;
	static int	semid;
	
	if((semid = semget((key_t)0x1234,1,IPC_CREAT|0666)) == -1){
		perror("shmget");
		exit(1);
	}
	
	sem_val=semctl(semid, 0, GETVAL, sem_ctrl);
	printf(" sema:%d\n ", sem_val);
	if(sem_val != 1)
		sem_val=1;
	sem_ctrl.val=sem_val;
	semctl(semid, 0, SETVAL, sem_ctrl);
	printf(" sema:%d\n ", sem_val);
	
	return 0;
}