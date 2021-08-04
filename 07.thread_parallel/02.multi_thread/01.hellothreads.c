#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD	3
// int i;
void *hello_thread(void *arg){
	int i;
	for(i=1; i<=3; i++) {
		printf("Thread %ld: Hello, World(%d)!\n", (long)arg, i);
		sleep(1);
	}
	return arg;
}

int main(void){
	pthread_t tid[NUM_THREAD];
	int status;
	long i;
	for(i=0; i<NUM_THREAD; i++) {
		status = pthread_create(&tid[i], NULL, hello_thread, (void *)i);
		if(status != 0) {
			perror("thread create");
			exit(1);
		}
	}
	printf("\e[31mMain Thread End!!\e[0m\n");
	// getchar();		//ps -efL
	pthread_exit(NULL);
    return 0;
}
