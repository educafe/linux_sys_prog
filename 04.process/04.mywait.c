#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

static void handler (int signo){
	printf ("\e[31m%s[%d] signal is caughted\n", sys_siglist[signo], signo);
	system("ps -l");
	printf("\e[00m");
}

int main (void){
	int status;
	pid_t pid;
	if(fork() == 0){
		printf("Child (%d) waiting for a signal\n", getpid());
		signal(SIGINT, handler);
		pause();
		exit(10);
	}
	printf("Parent (%d) waiting for termination of child\n", getpid());
	pid = wait(&status);
	printf("PID of Child terminated = %d\n", pid);
	if (pid == -1)
		perror ("wait");
	if (WIFEXITED(status))
		printf ("Normal termination with exit status=%d\n", WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		printf ("Killed by signal=%d%s\n", WTERMSIG(status), WCOREDUMP(status) ? " (dumped core)" : "");
	system("ps -l");
	return 0;
}

