#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE	1024

int main(int argc, char *argv[]){
	int fd;
	int ret;
	char buf[BUF_SIZE];
	if(argc < 2){
		printf("Usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("open()");
		exit(1);
	}
	while(1) {
		ret=read(fd, buf, BUF_SIZE);
		if(ret == 0){
			break;
		}
		buf[ret] = '\0';
		// printf("READ=%d, STRLEN=%lu\n", ret, strlen(buf));
		printf("%s", buf);
	}
	close(fd);
	return 0;
}

