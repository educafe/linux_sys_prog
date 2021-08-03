#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct _INFO {
	char name[20];
	int age;
	float height;
} INFO;

int main(int argc, char *argv[]){
	INFO data[5] = {"kim",20,170.1F,
					"lee",25,180.3F,
					"park",21,176.2F,
					"choi",28,167.9F,
					"kang",25,172.5F};
	int fd;
	int i;
	umask(0);
	if((fd=open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0664)) == -1) {
		perror("open");
		exit(1);
	}
	for(i=0; i<5; i++) {
		if(write(fd, &data[i], sizeof(INFO)) == -1) {
			perror("write");
			close(fd);
			exit(2);
		}
	}
	close(fd);
	return 0;
}
