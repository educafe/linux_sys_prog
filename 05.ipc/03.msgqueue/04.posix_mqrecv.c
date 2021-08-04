#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>

int main(int argc, char *argv[]){
	struct mq_attr attr;
	int value=1;
	char msg[128] = {0};
	mqd_t mqd;
	
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    memset( &attr, 0x00, sizeof(struct mq_attr) );
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 128;
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;
	
	mqd = mq_open("/myqueue", O_RDWR|O_CREAT, mode, &attr);	//메세지 큐 열기/생성
	mq_getattr(mqd, &attr);
	printf("# of messages currently on queue: %ld\n", attr.mq_curmsgs);
	
	while(1){
		mq_receive(mqd, (char *)msg, (size_t)attr.mq_msgsize, NULL);	//메시지 전송
		printf("\e[31mReceived data : %s\e[0m\n", msg);
		if(value++ == atoi(argv[1]))
			break;
	}
	mq_close(mqd);
	// mq_unlink("/myqueue");					//POSIX 메세지 큐 제거
	// printf("MQ Receiver is out\n");
	return 0;
}

