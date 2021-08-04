#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h>

void *thread_function(void *arg);

int main() {
	int status;
	pthread_t tid;
	void *return_value;
	int i;

	//쓰레드 생성
	// status = pthread_create(&tid, NULL, thread_function, (void *)NULL);
	status = pthread_create(&tid, NULL, thread_function, "hello thread\n");
	if(status !=0){
		perror("pthread_create");
		exit(1);
	}
	
	for(i=1; i<=5; i++){
		printf("Parent thread %d!!\n", i);
		sleep(1);
	}

	//쓰레드 종료 처리 대기
	status = pthread_join(tid, &return_value);
	if(status != 0){
		perror("pthread_join");
		exit(1);
	}
	printf("Thread joined, it returned %s\n", (char *)return_value);
	// printf("Thread joined, it returned %ld\n", (long)return_value);
	return 0;
}

void *thread_function(void *arg){
	int i;
	pid_t tpid, pid;

#ifdef DEBUG
	pthread_t thread_id;
	tpid = syscall(SYS_gettid);
	printf("\e[34mThread LWP: %d, Thread PID: %d\e[0m\n", tpid, getpid());
	
	thread_id = pthread_self();
	printf("\e[32mThread function ID: %u\e[0m\n", (unsigned int)thread_id);
#endif
	
	for(i=1; i<=10; i++){
		printf("\t\e[31mChild thread %d\e[0m\n", i);
		sleep(1);
	}
	return "Good Bye";
}
