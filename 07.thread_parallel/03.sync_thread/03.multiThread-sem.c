#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <semaphore.h>

//#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h> 


void * thread_function(void *);

pid_t tid;
#ifndef NOSEM
sem_t semid;
#endif

int main(void){
	pthread_t tid1, tid2;
	
#ifndef NOSEM
	if((sem_init(&semid, 0, 1)) != 0){	//0: 프로세스 내의 쓰레드간 세마포어 공유, 초기값 1
		perror("sem_init");
		exit(1);
	}
#endif

	if(pthread_create(&tid1, NULL, thread_function, NULL)!=0) {
		perror("pthread_create");
		exit(1);
	}
	
	if(pthread_create(&tid2, NULL, thread_function, NULL)!=0) {
		perror("pthread_create");
		exit(1);
	}
	
	if(pthread_join(tid1, NULL)!=0) {
		perror("pthread_join");
		exit(1);
	}
	if(pthread_join(tid2, NULL)!=0) {
		perror("pthread_join");
		exit(1);
	}
	
#ifndef NOSEM
	sem_destroy(&semid);
#endif

	return 0;
}

void * thread_function(void * arg){
	printf("THREAD1 TID=%ld\n", syscall(SYS_gettid));
	for(int i=0; i<200; i++) {
#ifndef NOSEM
		sem_wait(&semid);
#endif
		tid=syscall(SYS_gettid);
		for(int j=0; j<5000000; j++){}
		if(syscall(SYS_gettid) == tid)
			putchar('0');
		else
			putchar('X');
		fflush(stdout);
#ifndef NOSEM
		sem_post(&semid);
#endif

	}
	pthread_exit(NULL);
}
