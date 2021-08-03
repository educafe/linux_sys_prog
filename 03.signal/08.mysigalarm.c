#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <signal.h> 
#include <string.h>

void alarm_handler(int signo){
	printf("Time over, try again later---\n");
	exit(0);
}

int main(int argc, char *argv[]){
	char buf[512];
	char *passwd = "hello";
	struct sigaction act;
	if(argc <2){
		fprintf(stderr, "Usage: %s <timelimit>\n", argv[0]);
		exit(1);
	}
	act.sa_handler = alarm_handler;
	sigaction(SIGALRM, &act, NULL);
	alarm(atoi(argv[1]));
	while(1){
		printf("Input password: ");
		scanf("%s", buf);
		if(!strcmp(buf, passwd)){
			printf("Success\n");
			break;
		}else{
			printf("Fail\n");
		}
	}
	printf("Main function -----\n");
	return 0;
}

