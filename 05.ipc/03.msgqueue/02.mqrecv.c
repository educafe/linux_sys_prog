#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void){
	char buf[1024];
	ssize_t n;
	int msqid;
	struct msgbuf {
		long m_type;
		char m_text[1024];
	}recvbuf;
	msqid = msgget(0x222, IPC_CREAT | 0666);		//기존 메세지 큐를 구하거나 새로운 메세지 큐 객체 생성
	if(msqid == -1){
		perror("msgget error");
		exit(1);
	}
	while(1){
		n = msgrcv(msqid, &recvbuf, 1024, 0, 0);
		recvbuf.m_text[n] = '\0';
		printf("\e[31mRx: %s\e[0m", recvbuf.m_text);
		if(!strncmp(recvbuf.m_text,"end", 3)){
			break;
		}
	}
	if(msgctl(msqid, IPC_RMID, 0) == -1){		//메세지 큐 객체 삭제
		perror("msgctl error");
		exit(1);
	}
	return 0;
}
