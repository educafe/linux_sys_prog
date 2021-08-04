#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
	int fd, i;
	char buf[128];
	time_t timer1;
	
	if((fd = open("/tmp/myfifo", O_RDWR)) == -1){
		perror("open");
		exit(2);
	}
	
	for(i=0; i<5; i++){
		memset(buf, 0, sizeof(buf));
		sprintf(&buf[0], "Hello(%d)", i);
		write(fd, &buf[0], strlen(buf)+1);
		printf("Tx: %s\n", buf);
		for(timer1=time(NULL); time(NULL)<timer1 + 2;)
			continue;
	}
	memset(buf, 0, sizeof(buf));
	sprintf(buf, "end");
	write(fd, buf, strlen(buf)+1);
	close(fd);
	/* unlink("/tmp/mkfifo"); */
	return 0;
}

