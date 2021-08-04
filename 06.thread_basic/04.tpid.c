#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    pid_t tid, pid;

    tid = syscall(SYS_gettid);
	pid = syscall(SYS_getpid);
	printf("TID=%u\n", tid);
	printf("PID=%u\n", pid);
    syscall(SYS_tgkill, getpid(), tid, SIGHUP);
	return 0;
}
