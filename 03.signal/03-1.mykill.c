#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

int send_signal(int pid){
	int ret;
	for(int i=1; i<=64; i++){
		if(i==9 || i==32 || i==33)
			continue;
		if(i==18){
			kill(pid, 19);
			printf("Signal #(19) sent\n");
			sleep(2);
			continue;
		}
		if(i==19){
			kill(pid,18);
			printf("Signal #(18) sent\n");
			sleep(2);
			continue;
		}
			
		if((kill(pid, i)) == -1){
			if(errno == EINVAL){
				printf("Invalid signal\n");
			}else if(errno == EPERM){
				printf("No Permission\n");
			}else if(errno == ESRCH){
				printf("No such process\n");
			}
		}
		printf("Signal #(%d) sent\n", i);
		sleep(1);
	}
}

int get_pid(){
	char pidof[128];
	int pid;
	
    FILE *fp = popen("pidof a.out","r");
    fgets(pidof,128,fp);
    // printf("%s",pidof);
    pclose(fp);
	pid = atoi(pidof);
	// printf("%d",pid);
	return pid;
}


int main(int argc, char *argv[]){
	
	int pid, signo;
		
	pid = get_pid();
	send_signal(pid);
	return 0;
}