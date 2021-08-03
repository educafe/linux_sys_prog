#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
	FILE *fp;
	size_t ret;
	char data[512];	
	if((fp = fopen(argv[1], "r")) == NULL){
		perror("fopen");
		exit(1);
	}
	memset(data, 0, sizeof(data));
	while(1) {
		ret=fread(data, sizeof(char), sizeof(data), fp);
#if 1
		puts(data);
#else
		// data[ret]='\0';
		// printf("RET=%lu, STRLEN=%lu\n", ret, strlen(data));
		printf("%s", data);
#endif
		if (feof(fp)) {
			break;
		}
	}
	fclose(fp);
	return 0;
					
}

