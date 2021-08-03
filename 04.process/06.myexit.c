#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void handler(int signo
	int status=0;
	printf ("%s[%d] signal is caughted\n", sys_siglist[signo], signo);
	if((waitpid(-1, &status, WUNTRACED | WCONTINUED)) == -1){
        perror("waitpid");
    }
	if (WIFEXITED(status)) {
        printf("exited, status=%d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
		if(WTERMSIG(status) && WCOREDUMP(status))
			printf("terminated and coredumped by signal[%d]\n" , WTERMSIG(status));
		else 
			printf("terminated by signal[%d]\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        printf("stopped by signal[%d]\n", WSTOPSIG(status));
    } else if (WIFCONTINUED(status)) {
        printf("continued\n");
    }
}

void handler2(int signo) {
	printf ("%s[%d] signal is caughted\n", sys_siglist[signo], signo);
}

int main(int argc, char *argv[]) {
	pid_t pid;
	signal(SIGCHLD, handler);
	pid = fork();
    if (pid == -1) {
        perror("fork");
        _exit(EXIT_FAILURE);
    }
	if(pid == 0){            /* Code executed by child */
        printf("Child PID is %ld\n", (long) getpid());
        if (argc == 2) {
			signal(SIGINT, handler2);
			pause();  
			sleep(1);
			 _exit(atoi(argv[1]));
		}
        _exit(10);
	}else{                    /* Code executed by parent */
		while(1) {
			if((waitpid(-1, NULL, WNOHANG)) == -1)
				break;
		}
    }
}

