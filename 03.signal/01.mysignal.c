#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int repeat = 0;

void handler(int signo){
	fprintf(stdout, "Signal handler triggered %d times (signum=%d)\n", repeat++, signo);
	if(repeat >= 5)
		signal(SIGINT, SIG_DFL);
}

int main(int argc, char *argv[]){
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGSTOP, handler);
	signal(SIGTERM, SIG_IGN);
	while(1){
		printf("signal interrupt test --- %d\n", repeat);
		sleep(1);
	}
	
	return 0;
}

