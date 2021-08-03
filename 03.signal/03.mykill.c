#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>


int main(int argc, char *argv[]){
	
	if(argc < 3){
		fprintf(stderr, "Usage: %s <pid_#> <sig_#>\n", argv[0]);
		exit(1);
	}
	
	if(kill(atoi(argv[1]), atoi(argv[2])) == -1){
		if(errno == EINVAL){
			printf("Invalid signal\n");
		}else if(errno == EPERM){
			printf("No Permission\n");
		}else if(errno == ESRCH){
			printf("No such process\n");
		}
	}
	return 0;
}

