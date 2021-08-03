#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	char cmd_buf[256];
	int ret;
	
	printf("--------------system start--------------\n");
#if 1
	strcpy(cmd_buf, "./01.mytask 10");
#else
	strcpy(cmd_buf, "ps -f");
#endif
	ret = system(cmd_buf);
	printf("--------------system end-----------%d-----\n", ret);
	 
	return 0;
}

