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

int main(int argc, char *argv[]) {
	INFO *data;
	int fd;
	struct stat fileinfo;
	int file_size, data_no;
	int i;

	if((fd=open(argv[1], O_RDONLY))==-1) {
		perror("open");
		exit(1);
	}

	stat(argv[1], &fileinfo);
	file_size = fileinfo.st_size;
	data_no = file_size/sizeof(INFO);

	if((data = (INFO *)malloc(sizeof(INFO) * data_no)) == NULL) {
		perror("malloc");
		close(fd);
		exit(2);
	}

	if(read(fd, data, sizeof(INFO)*data_no) != sizeof(INFO)*data_no) {
		perror("write");
		close(fd);
		exit(3);
	}

	for(i=0; i<data_no; i++)
	{
		printf("name:%s, age:%d, height:%.1f\n", data[i].name, data[i].age, data[i].height);
	}

	close(fd);
	return 0;
}
