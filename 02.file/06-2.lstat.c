#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	struct stat buf;
	char *msg;

	if(argc < 2) {
		fprintf(stderr, "Usage : %s filename\n", argv[0]);
		exit(1);
	}
	
	if(lstat(argv[1],&buf)==-1) {
			if(errno==ENOENT) 
				fprintf(stderr, "%s is not found\n", argv[1]);
			else if(errno==EACCES)
				fprintf(stderr, "No permission for %s\n",argv[1]);
			exit(2);
	}
	
	switch (buf.st_mode & S_IFMT) {
		case S_IFBLK:  msg = "block device";            break;
		case S_IFCHR:  msg = "character device";        break;
		case S_IFDIR:  msg = "directory";               break;
		case S_IFIFO:  msg = "FIFO/pipe";               break;
		case S_IFLNK:  msg = "symbolic link";           break;
		case S_IFREG:  msg = "regular file";            break;
		case S_IFSOCK: msg = "socket";                  break;
		default:       msg = "unknown?";                break;
	}
	printf("%s is %s.\n", argv[1], msg);
		
	return 0;
}

// /usr/include/x86_64-linux-gnu/sys/stat.h
// # define S_IFMT         __S_IFMT
// /usr/include/x86_64-linux-gnu/bits
// #define __S_IFMT        0170000 /* These bits determine file type.  */
