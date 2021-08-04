#include <stdio.h>
#include <unistd.h>  
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define  MEM_SIZE    1024

int main() {
	int fd;
	void *shm_addr;
	int count=0;
	
	fd = shm_open("/mydata", O_RDONLY, 0666);
	if(fd == -1){
		perror("shm_open");
		exit(1);
	}
	
	//메모리 객체 매핑
	shm_addr = mmap(0, MEM_SIZE, PROT_READ, MAP_SHARED, fd, 0);
	if(shm_addr == (void *)-1){
		perror("mmap error");
		return EXIT_FAILURE;
	}
	
	printf( "Map addr is %p\n", shm_addr );
	
	printf("Read message: \e[31m%s\e[0m\n", (char *)shm_addr);
	
	close(fd);
	
	shm_unlink("/mydata");
	return 0;
}

