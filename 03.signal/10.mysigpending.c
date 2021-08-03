#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "signalprint.h"

static void handler(int signo) { 
	printf("Signal #(%d) caught\n", signo); 
}

int main( void){
	sigset_t sigset, oldset, pendingset;
	int i = 0;
	for(i=1; i<=31; i++){
		signal(i, handler);
	}
	sigfillset(&sigset);
	sigprocmask(SIG_SETMASK, &sigset, &oldset);
	while(1){
		printf( "Count__: %d\n", i++);
		sleep(5);
		if (sigpending(&pendingset) == 0){
			print_sigset_t(&pendingset);
			if (sigismember(&pendingset, SIGINT)){
				printf( "Pressed Ctrl-C,,, end of loop.\n");
				break;
			}
			if(sigismember(&pendingset, SIGTSTP)){
				printf( "Pressed Ctrl-Z,,, end of loop.\n");
				break;
			}
		}
   }
   sigprocmask(SIG_SETMASK, &oldset, NULL);
   return 0;
}

