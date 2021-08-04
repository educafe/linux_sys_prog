#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <errno.h>

pid_t tid;
pthread_mutex_t mutex_id;
void *thread1(void *arg) {
	printf("THREAD1 TID=%ld\n", syscall(SYS_gettid));
	for(int i=0; i<300; i++) {
		pthread_mutex_lock(&mutex_id);
		tid=syscall(SYS_gettid);
		for(int j=0; j<5000000; j++){}
		if(syscall(SYS_gettid) == tid)
			putchar('0');
		else
			putchar('X');
		fflush(stdout);
		pthread_mutex_unlock(&mutex_id);
	}
	return NULL;
}
void *thread2(void *arg) {
	printf("THREAD2 TID=%ld\n", syscall(SYS_gettid));
	for(int i=0; i<200; i++) {
		pthread_mutex_lock(&mutex_id);
		tid=syscall(SYS_gettid);
		for(int j=0; j<10000000; j++){}
		if(syscall(SYS_gettid) == tid)
			putchar('0');
		else
			putchar('X');
		fflush(stdout);
		pthread_mutex_unlock(&mutex_id);
	}
	return NULL;
}


int main() {
	
	if(pthread_mutex_init(&mutex_id, NULL) != 0){
		perror("pthread_mutex_init");
		exit(errno);
	}
	
	if (pthread_create(&tid1, NULL, thread1, NULL) != 0) {
		exit(1);
	}
	if (pthread_create(&tid2, NULL, thread2, NULL) != 0) {
		exit(1);
	}
	if(pthread_join(tid1, NULL) != 0) {
		perror("pthread_join");
		exit(1);
	}
	
	if(pthread_join(tid2, NULL) != 0) {
		perror("pthread_join");
		exit(1);
	}

	pthread_mutex_destroy(&mutex_id);
	return 0;
}