#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signo){
	printf("Received Signal no - %d\n", signo);
}

int main(int argc, char *argv[]){
	int a,b;
	
	for(int i=1; i<31; i++){
		if(signal(i, handler) == SIG_ERR){
			fprintf (stderr, "Cannot handle signal=%d\n", i);
		} 
	}
	for(int i=0; i<31; i++){
		if(i!=9){
			// kill(getpid(), i);
			raise(i);
			sleep(2);
		}
	}
	return 0;
}