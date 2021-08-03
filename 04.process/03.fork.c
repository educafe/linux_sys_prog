#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int a=10;
int b;

int main() {
	int c=100, c2;
	char *d = "parent";
	char *name;
	void *phone;
	pid_t pid;
	
	name = malloc(50);
	phone = malloc(20*sizeof(int));
	
	pid=fork();
	if(pid == 0){
		printf("\e[31mI am child[%d] of ppid[%d]\n", getpid(), getppid());
		a=200; b=400; c=600; d="I am child";
		printf("addr(TEXT)=> main:%p\n", main);
		printf("addr(CONST)=> d:%p, d_value:%s\n", d, d);
		printf("addr(DATA)=> a:%p, a_value:%d\n", &a, *(&a));
		printf("addr(BSS)=> b:%p, b_value:%d\n", &b, *(&b));
		printf("addr(STACK)=> c:%p, c_value:%d\n", &c, *(&c));
		printf("addr(HEAP)=> name:%p, phone:%p\n", name, phone);
	}else{
		printf("\e[00m%s[%d] of ppid[%d]\n", d, getpid(), getppid());
		printf("addr(CONST)=> d:%p, d_value:%s\n", d, d);
		printf("addr(CONST)=> d:%p\n", d);
		printf("addr(DATA)=> a:%p, a_value:%d\n", &a, *(&a));
		printf("addr(BSS)=> b:%p, b_value:%d\n", &b, *(&b));
		printf("addr(STACK)=> c:%p, c_value:%d\n", &c, *(&c));
		printf("addr(HEAP)=> name:%p, phone:%p\n", name, phone);
	}
	getchar();
	return 0;
}