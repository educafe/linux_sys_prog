#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void) {
	char buf[1024];
	int msqid;
	struct msgbuf{
		long m_type;
		char m_text[1024];
	}sendbuf;
	
	msqid = msgget(0x222, IPC_CREAT | 0666);	//메세지 큐 생성
	
	while(1){									//메세지 전송
		printf("Input Message -> ");
		fgets(buf, 1024, stdin);
		sendbuf.m_type = 1;						//메세지 타입 지정
		strcpy(sendbuf.m_text, buf);
		msgsnd(msqid, &sendbuf, strlen(sendbuf.m_text), 0);	//0: wait till queue space is available
		if(!strncmp(buf, "end", 3)){
			break;
		}
	}
#if 0
	if(msgctl(msqid, IPC_RMID, 0) == -1){		//메세지 큐 객체 삭제
		perror("msgctl error");
		exit(1);
	}
#endif
	return 0;
}
