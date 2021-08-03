#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	struct stat stat;
	char *msg;

	if(argc < 2) {
		fprintf(stderr, "Usage : %s filename\n", argv[0]);
		exit(1);
	}
	
	if(lstat(argv[1],&stat)==-1) {
		if(errno==ENOENT) 
			fprintf(stderr, "%s is not found\n", argv[1]);
		else if(errno==EACCES)
			fprintf(stderr, "Permission denied in directories of \"%s\" path\n",argv[1]);
		exit(2);
	}
	
	printf("st_mode = %o\n", stat.st_mode);
	
	if(S_ISREG(stat.st_mode)) msg = "regular file";
	else if(S_ISDIR(stat.st_mode)) msg = "directory";
	else if(S_ISCHR(stat.st_mode)) msg = "chracter special file";
	else if(S_ISBLK(stat.st_mode)) msg = "block special file";
	else if(S_ISFIFO(stat.st_mode)) msg = "pipe of FIFO";
	else if(S_ISLNK(stat.st_mode)) msg = "symbolic link";
	else if(S_ISSOCK(stat.st_mode)) msg = "socket";
	
	printf("%s is %s.\n", argv[1], msg);
		
	return 0;
}

