#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define  KEY_NUM     0x2222
#define  MEM_SIZE    1024

int main() {
	int shm_id;
	void *shm_addr, *shm_addr_dt;
	int count=0;
	
	if((shm_id = shmget((key_t)KEY_NUM,MEM_SIZE,IPC_CREAT|0666)) == -1){
		perror("shmget");
		exit(1);
	}
	
	if((shm_addr = shmat(shm_id, NULL, 0)) == (void *)-1){
		perror("shmat");
		exit(1);
	}
	shm_addr_dt = shm_addr;
	
	while(1){
		printf("\t\e[31mRead counter %s\e[0m\n", (char *)shm_addr);
		if(!strcmp(shm_addr, "end")){
			break;
		}
		shm_addr = shm_addr + sizeof(int);
		sleep(1);
		if(count == 6){
			count = 0;
			shm_addr = shm_addr_dt;
		}
		count++;
	}
	if(shmdt(shm_addr_dt) !=0){
		perror("shmdt");
		exit(2);
	}
	return 0;
}