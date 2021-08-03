#include <stdio.h> 
#include <signal.h> 
#include <unistd.h>
#include <stdlib.h>
#include "signalprint.h"

static void handler(int signo) { 
	printf ("%s[%d] signal is caughted\n", sys_siglist[signo], signo);
} 

int main() { 
	sigset_t set1,set2; 
	signal(SIGINT, handler); 
	
	sigemptyset(&set1); 
	sigaddset(&set1,SIGINT); 
	sigfillset(&set2); 
	sigdelset(&set2, SIGINT);
	
	sigprocmask(SIG_BLOCK,&set1,NULL); 
	print_sigset_t(&set1);
	print_sigset_t(&set2);
	
	printf("\ncritical region 1\n"); 
	sleep(5); 
	printf("\ncritical region 1 ends\n"); 
#if 1
	sigsuspend(&set2);
	printf("After suspend");
#else
	sigprocmask(SIG_SETMASK, &set2, NULL); 	
	pause();
	printf("After pause");
#endif
	printf("\ncritical region 2\n"); 
	sleep(10); 
	printf("\ncritical region 2 ends\n"); 
	exit(0); 
}