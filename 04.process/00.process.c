#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int a=10, a2=20;
int b, b2;

int f1(int x){
	return ++x;
}

int f2(int x){
	return --x;
}

int main(){
	int c=100, c2;
	char *d = "\e[31mThis is virtual memory layout of the process\e[00m";
	char *name;
	void *phone;
	
	name = malloc(40);
	phone = malloc(20*sizeof(int));
	name = "educafe";
	phone = "010-9093-3728";
	
	printf("%s\n", d);
	printf("addr(TEXT)=> \tmain:%p, f1:%p, f2:%p\n", main, f1, f2);
	printf("addr(CONST)=> \td:%p : %s\n", d, d);
	printf("addr(DATA)=> \ta:%p, a2:%p, a_value:%d, a2_value:%d\n", &a, &a2,*(&a), *(&a2));
	printf("addr(BSS)=> \tb:%p, b2:%p, b_value:%d, b2_value:%d\n", &b, &b2, *(&b), *(&b2));
	printf("addr(HEAP)=> \tname:%p, phone:%p, name:%s, phone:%s\n", name, phone, name, (char *)phone);
	printf("addr(STACK)=> \tc:%p, c2:%p\n", &c, &c2);
	sleep(1);
	return 0;
}



