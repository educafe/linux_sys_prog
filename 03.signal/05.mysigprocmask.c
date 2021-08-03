#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "signalprint.h"

void handler(int signo){
	printf ("%s[%d] signal is caughted\n", sys_siglist[signo], signo);
}

int main(void) {
	sigset_t set1, set2, set3;
	
	signal(SIGINT, handler);
	
	// for(int i=0; i<2000000000; i++) ;
	sleep(5);
	
	sigemptyset(&set1);	
	sigaddset(&set1, 2);
	printf("signals in set1 are blocked\n");
	printf("set1 : ");
	print_sigset_t(&set1);	
	sigprocmask(SIG_SETMASK, &set1, NULL);  
	
	for(int i=0; i<2000000000; i++) ;
	
	sigemptyset(&set2);							
	sigaddset(&set2, SIGQUIT);  
	printf("Signals in set2 are blocked and signals in set1 still remain blocked..... \n");	
	printf("set2 : ");
	print_sigset_t(&set2);	
	sigprocmask(SIG_BLOCK, &set2, NULL);

	for(int i=0; i<2000000000; i++) ;
	
	sigfillset(&set3);							
	printf("The set of blocked signal is set to set3\n");
	printf("set3 : ");
	print_sigset_t(&set3);
	sigprocmask(SIG_SETMASK, &set3, &set1);	
	printf("set1 : ");
	print_sigset_t(&set1);
	
	for(int i=0; i<2000000000; i++) ;
	
	printf("Signals in set1 are unblocked\n");
	sigprocmask(SIG_UNBLOCK, &set1, NULL);			
		
	while(1) {    
		printf("Hello Signal\n");    
		sleep(1);  
	}
	return 0;
}
