#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h> 


void * thread_function(void *);

int Counter=0;

int main(void)
{
	pthread_t tid1, tid2;
	void *thread_result;

	if(pthread_create(&tid1, NULL, thread_function, "thread1")!=0) {
		perror("pthread_create");
		exit(1);
	}
	
	if(pthread_create(&tid2, NULL, thread_function, "thread2")!=0) {
		perror("pthread_create");
		exit(1);
	}

	if(pthread_join(tid1, &thread_result)!=0) {
		perror("pthread_join");
		exit(1);
	}
	if(pthread_join(tid2, &thread_result)!=0) {
		perror("pthread_join");
		exit(1);
	}

	printf(" thread result : %s\n", (char *) thread_result);
	return 0;
}

void * thread_function(void * arg)
{
	int temp;
	int i, j;
	char buffer[80];

	printf("thread_function called\n");
	
	for(i=0; i<8; i++) {
		sprintf(buffer, "%s: CountRelay: from %d to ", (char*)arg, Counter);
		write(1, buffer, strlen(buffer));

		temp=Counter;
		temp=temp+1;

// delay
		for(j=0; j<500000; j++);

		// Counter=temp+1;
		Counter=temp;

		sprintf(buffer, "\e[31m%d\e[0m\n", Counter);
		write(1, buffer, strlen(buffer));

		// for(j=0; j<50000000; j++);

	}
	// getchar();
	pthread_exit("thread end");
}
