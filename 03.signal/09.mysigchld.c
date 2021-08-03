#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo){
	int ret;
	int status;
	
	printf("Signal Handler starts -----\n");
	for(;;){
		ret = waitpid(-1, &status, WNOHANG);
		if(ret == 0){
			break;
		}
		if(ret == -1 && errno == ECHILD){
			printf("No Child --\n");
			break;
		}
		if(ret == -1){
			perror("child waitpid");
			abort();
		}
		printf("\e[31mPID %d child process is dead\e[0m\n", ret);
		
	}
	printf("Signal Handler ends -----\n");
	
}

int main(void) {
	int i;
	
	signal(SIGCHLD, handler);
	
	switch(fork()){
		case -1:
			exit(1);
			// break;
		case 0:
			printf("\t\tChild 1 process --- (%d)\n", getpid());
			for(i=0; i<5; i++){
				printf("\t\tChild process 1 is running ---(%d)\n", getpid());
				sleep(1);
			}
			exit(0);
			// break;
		default:
			switch(fork()){
				case -1:
					exit(1);
					// break;
				case 0:
					printf("\tChild 2 process --- (%d)\n", getpid());
					for(i=0; i<10; i++){
						printf("\tChild 2 process is running --- (%d)\n", getpid());
						sleep(1);
					}
					exit(0);
					// break;
				default:
					printf("Parent starts working --- (%d)\n", getpid());
					// break;
			}
	}
	while(1){
		printf("Parent is working --- (%d)\n", getpid());
		sleep(1);
	}
	
	return 0;
}