#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

time_t startTimel, startTimes, startTimep;
pid_t ret_pid;

void handler(int signo) {
	printf ("\n%s[%d] signal is caughted\n", sys_siglist[signo], signo);
	if((ret_pid = waitpid(-1, NULL, WNOHANG)) > 0) {
		printf("Terminated child PID = %d\n", ret_pid);
	} else if (errno == ECHILD){
		printf("No Child\n");
	}
}

int main(void) {
	pid_t ret1, ret2;
	
	signal(SIGCHLD, handler);
	switch(ret1 = fork()){
		case -1:		// fork error
			perror("fork"); 
			exit(1);
		case 0:						//Child 1
			for (startTimel = time(NULL); time(NULL) < startTimel + 8;){
				for(int i=0; i<100000000; i++);
				write(1, "+", 1);
			}
			system("ps -l");
			exit(0);
		default:					//Parent
			for (startTimep = time(NULL); time(NULL) < startTimep + 10;){
				for(int i=0; i<100000000; i++);
				write(1, "*", 1);
			}
			printf("\n");
			system("ps -l");
	}
	return 0;
}




