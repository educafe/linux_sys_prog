#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <semaphore.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h> 


void * thread_function(void *);

pid_t tid;
sem_t *semp, semid;

int main(void){
	pthread_t tid1, tid2;
	int flags;
	mode_t perms;

#ifndef NOSEM
	flags = O_CREAT | O_EXCL;
	perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;	//rw-rw-rw-
	semp = sem_open("mysem", flags, perms, 1);
	if (semp == SEM_FAILED){
		perror("sem_open");
		exit(2);
	}
	semid = *semp;
#endif

	if(pthread_create(&tid1, NULL, thread_function, "thread1")!=0) {
		perror("pthread_create");
		exit(1);
	}
	
	if(pthread_create(&tid2, NULL, thread_function, "thread2")!=0) {
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
	sem_close(semp);
	sem_unlink("mysem");
	// sem_unlink((const char *)semp);
	exit(EXIT_SUCCESS);
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
