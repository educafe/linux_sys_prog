#include <stdio.h>
#include <unistd.h>  
#include <sys/mman.h>
#include <sys/stat.h>       
#include <fcntl.h>
#include <string.h>

#define  MEM_SIZE    1024

int main() {
	int fd;
	void *shm_addr;
	const char *message0= "This is ";
	const char *message1= "Linux Systems ";
	const char *message2= "Programming!";
	
	//메모리 객체 생성
	fd = shm_open("/mydata", O_RDWR | O_CREAT, 0666);
	
	//메모리 객체 크기 설정
	ftruncate(fd, MEM_SIZE);
		
	//메모리 객체 매핑
	shm_addr = mmap(0, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	printf( "Map addr is %p\n", shm_addr );
	
	sprintf(shm_addr, "%s", message0);
	shm_addr += strlen(message0);
	sprintf(shm_addr, "%s", message1);
	shm_addr += strlen(message1);
	sprintf(shm_addr, "%s", message2);
	shm_addr += strlen(message2);
	
	close(fd);
	return 0;
}

