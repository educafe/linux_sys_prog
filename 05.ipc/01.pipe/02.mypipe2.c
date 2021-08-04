#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MSGSIZE	64

int main(void){
	int pd[2];
	pid_t ret;
	time_t timer1;
	char buf[MSGSIZE];
	int i, len;
	
	if(pipe(pd) == -1){
		perror("pipe");
		exit(1);
	}
	
	switch(fork()){
		case 0:					//child
			close(pd[0]);
			for(i=0; i<10; i++) {
				sprintf(&buf[0], "Hello, Parent #%d", i+1);
				write(pd[1], buf, strlen(buf));
				for(timer1=time(NULL); time(NULL)<timer1 + 1;)
					continue;
			}
			exit(0);
		default:				//parent
			close(pd[1]);
			for(i=0; ; i++) {
				memset(&buf[0], 0, MSGSIZE);
				len = read(pd[0], buf, MSGSIZE);
				if(len == 0){
					break;
				}
				printf("PARENT: %s\n", buf);
			}
	}
	return 0;
}

