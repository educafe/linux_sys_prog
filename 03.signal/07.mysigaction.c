#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "signalprint.h"

void handler(int sig){
	sigset_t sigset;
    sigprocmask(SIG_SETMASK, NULL, &sigset);
	printf("blocked signal set : ");
	print_sigset_t(&sigset);
	for(int i=1; i<=3; i++) {
		printf("handler_%d!!\n", i);
		sleep(1);
	}
}
	
int main(void){
	struct sigaction act, oldact;
	
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGQUIT);
	
	// act.sa_flags=SA_NODEFER;
	act.sa_flags=SA_RESTART;
	// act.sa_flags=SA_RESETHAND;
	sigaction(SIGINT, &act, &oldact);
	
	while(1){
		printf("signal test\n");
		sleep(2);
	}
	return 0;
}

