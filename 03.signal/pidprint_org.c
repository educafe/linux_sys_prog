#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	char pidof[128];
	int pid;
	FILE *fp = popen("pidof a.out","r");
	fgets(pidof,128,fp);
	printf("%s\n",pidof);
	pclose(fp);
	pid = atoi(pidof);
	printf("%d\n",pid);
}