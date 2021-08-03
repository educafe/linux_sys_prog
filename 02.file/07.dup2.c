#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int fd;
	char *buf = "This is a dup() demonstration\n";
	
	if((fd = open(argv[1], O_WRONLY |O_CREAT|O_TRUNC, 0644)) == -1){
		perror("open");
		exit(1);
	}

#if 0
	close(1);
	dup(fd);
#else
	dup2(fd, 1);	//stdout redirected to fd 
#endif
	close(fd);
	write(1, buf, strlen(buf));
	printf("Hello World ~~~\n");
	fprintf(stdout, "This is the output to stdout\n");
	getchar();
	
	return 0;
}
