#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	int i, fd;
	pid_t pid, ppid;
	pid=getpid();
	ppid=getppid();
	
	printf("%s PID = %d\n", argv[0], pid);
	printf("%s PPID = %d\n", argv[0], ppid);
	
	if((fd = open("/dev/null", O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1){
		perror("open");
		exit(1);
	}
	
#if 1
	dup2(fd, 1);
#endif
	
	for(i=1; i<=atoi(argv[1]); i++) {
		printf("MyTask_%d!!\n", i);
		sleep(1);
	}
	return 0;
}

