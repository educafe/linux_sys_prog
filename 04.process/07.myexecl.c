#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int a=1000;
int b;

int main(void) {
	pid_t pid;
	int status;
	int c=10000, c2;
	char *d = "parent";
	char *name;
	void *phone;
	
	name = malloc(50);
	phone = malloc(20*sizeof(int));

	switch (pid=fork()) {
		case -1:
				perror("fork failed");
				break;
		case 0:				// child process
				printf("CHILD PROCESS : %d\n", getpid());
#if 1
				execl("./00.process", "00.process", (char *)0);
#else
				char *args[] = {"01.mytask", "10", NULL};
				if(execv("./01.mytask", args) == -1)
					perror("execv");
#endif
		default:
			printf("PARENT PROCESS : %d\n", getpid());
			printf("%s[%d] of ppid[%d]\n", d, getpid(), getppid());
			printf("addr(CONST)=> d:%p, d_value:%s\n", d, d);
			printf("addr(DATA)=> a:%p, a_value:%d\n", &a, *(&a));
			printf("addr(BSS)=> b:%p, b_value:%d\n", &b, *(&b));
			printf("addr(HEAP)=> name:%p, phone:%p\n", name, phone);
			printf("addr(STACK)=> c:%p, c_value:%d\n", &c, *(&c));
			system("ps -l");
			pid = wait(&status);
			printf("parent : completed!\n");
			exit(0);
	}
	return 0;
}

