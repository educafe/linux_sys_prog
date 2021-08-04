#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	struct mq_attr attr;
	char msg[128]={0};
	mqd_t mqd;
	int value=1;
	
    memset( &attr, 0x00, sizeof(struct mq_attr) );
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 128;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;
	
	mqd = mq_open("/myqueue", O_RDWR|O_CREAT, mode, &attr);		//메세지 큐 열기/생성
	
	while(1){
		sprintf(msg, "hello world[%d]", value);
		mq_send(mqd, (char *)msg, strlen(msg), 1);		//메시지 전송
		printf("Send data : %s\n", msg);
		if(value++ == atoi(argv[1])){
			break;
		}
		sleep(1);
	}
	mq_close(mqd);
	return 0;
}

