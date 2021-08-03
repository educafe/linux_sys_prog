#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo){
	printf("Received Signal no - %d\n", signo);
}

int main(int argc, char *argv[]){
	int a,b;
	
	for(int i=1; i<64; i++){
		if(signal(i, handler) == SIG_ERR){
			fprintf (stderr, "Cannot handle signal=%d\n", i);
		} 
	}
	for(int i=0; i<64; i++){
		if(i!=9 && i!=32 && i!=33){
			// kill(getpid(), i);
			raise(i);
			sleep(1);
		}
	}
	return 0;
}

