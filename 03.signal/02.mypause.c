#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void handler (int signo){
	printf ("%s[%d] signal is caughted\n", sys_siglist[signo], signo);
	// exit (EXIT_SUCCESS);
}
int main (void){
	char prompt[]="Waiting for a signal : ";
	signal(SIGTERM, SIG_DFL);
	for(int i=1; i<31; i++){
		if(signal(i, handler) == SIG_ERR){
			fprintf (stderr, "Cannot handle signal=%d\n", i);
		} else if (signal (SIGTERM, SIG_DFL) != SIG_DFL){
			fprintf (stderr, "default action signal=%d\n", i);
		}
	}
	for (;;){
		write(1, prompt, sizeof(prompt));
		pause ();
	}
	return 0;
}

