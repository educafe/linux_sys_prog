#include <stdio.h>
#include <signal.h>
#include <unistd.h>

const char *binary[16] = {
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};

void print_byte(int byte){
    // printf("%s%s", bit_rep[byte >> 4], bit_rep[byte & 0x0F]);
	printf("%s", binary[byte & 0x0F]);
}

void print_sigset_t(sigset_t *set){
	int i;

	// i = SIGRTMAX;
	i = 32;
	do {
		int x = 0;
		i -= 4;
		if (sigismember(set, i+1)) x |= 1;
		if (sigismember(set, i+2)) x |= 2;
		if (sigismember(set, i+3)) x |= 4;
		if (sigismember(set, i+4)) x |= 8;
		// printf("%x", x);
		print_byte(x);
	} while (i >= 4); 
	printf("\n");
}

// int main(int argc, char **argv)
// {
	// sigset_t set;
	// sigemptyset(&set);
	// /* add signals to set */
	// sigaddset(&set, SIGINT); 		//sig # 2
	// sigaddset(&set, SIGHUP);		//sig # 1
	// sigaddset(&set, SIGALRM);		//sig # 14
	// sigaddset(&set, SIGFPE);		//sig # 8
	// sigaddset(&set, SIGABRT);		//sig # 6
	// /* dump signals from set*/	
	// print_sigset_t(&set);
// }