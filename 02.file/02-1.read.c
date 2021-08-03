#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct _INFO {
	char name[20];
	int age;
	float height;
} INFO;

int main(int argc, char *argv[]){
	int fd;
	INFO data;
	int ret;
	
	if(argc < 2){
		printf("Usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	
	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("open()");
		exit(1);
	}
	
	while(1){
		ret = read(fd, &data, sizeof(INFO));
		if(ret == 0)
				break;
		printf("Name: %s, Age: %d, Height: %.1f\n", data.name, data.age, data.height);
	}
	close(fd);
	
	return 0;
}