#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/syscall.h>
#include <sys/types.h>

pid_t tid;

pthread_t	tid1, tid2;	/* thread ID */
void *thread1(void *arg) {
	printf("THREAD1 TID=%ld\n", syscall(SYS_gettid));
	for(int i=0; i<300; i++) {
		tid=syscall(SYS_gettid);
		for(int j=0; j<5000000; j++){}
		if(syscall(SYS_gettid) == tid)
			putchar('0');
		else
			putchar('X');
		fflush(stdout);
	}
	return NULL;
}

void *thread2(void *arg) {
	printf("THREAD2 TID=%ld\n", syscall(SYS_gettid));
	for(int i=0; i<200; i++) {
		tid=syscall(SYS_gettid);
		for(int j=0; j<10000000; j++){}
		if(syscall(SYS_gettid) == tid)
			putchar('0');
		else
			putchar('X');
		fflush(stdout);
	}
	return NULL;
}


int main() {
	
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

	return 0;
}