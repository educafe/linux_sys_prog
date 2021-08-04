#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h>

void *thread_function(void *arg);

int main() {
	int status;
	pthread_t tid;
	void *thread_result;
	int i;
	
#ifdef DEBUG
	pid_t tpid;
	tpid = syscall(SYS_gettid);
	printf("\e[35mParent LWP: %d, Parent PID: %d\e[0m\n", tpid, getpid());
#endif
	
	//쓰레드 생성
	// status = pthread_create(&tid, NULL, thread_function, (void *)NULL);
	status = pthread_create(&tid, NULL, thread_function, "hello thread");
	if(status !=0){
		perror("pthread_create");
		exit(1);
	}
	printf("Created Thread ID = %u\n", (unsigned int)tid);
	
	for(i=1; i<=5; i++){
		printf("Parent thread %d!!\n", i);
		sleep(1);
	}
	return 0;
}

void *thread_function(void *arg){
	int i;
	pid_t tpid, pid;
	
#ifdef DEBUG
	tpid = syscall(SYS_gettid);
	printf("\e[34mThread LWP: %d, Thread PID: %d\e[0m\n", tpid, getpid());
#endif
#if 1
	pthread_t thread_id;
	thread_id = pthread_self();
	printf("\e[32mThread ID: %u\e[0m\n", (unsigned int)thread_id);
#endif

	for(i=1; i<=10; i++){
		printf("\t\e[31mChild thread[%d] - %s\e[0m\n", i, (char *)arg);
		sleep(1);
	}
	return NULL;
}
