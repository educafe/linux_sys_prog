#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#if 0
_Thread_local int t;
/* 
* Variables marked with _Thread_local are given "thread" storage duration -- that is, 
* they are allocated when a thread begins, and deallocated when the thread ends
*/
#else
int t;
#endif

void swap(int *x, int *y) {
	t = *x;
	*x = *y;
	
	for(int i=0; i<1000000; i++) ;
/* while performing for loop, there might be an task switching between threads */
	*y = t;
}

pthread_t	tid1, tid2;	/* thread ID */
void *thread1(void *arg) {
	pthread_detach(pthread_self());
	int a=100, b=200;
	// for(int i=0; i<1000000; i++) ;
	
	swap(&a, &b);
	printf("A=%d, B=%d\n", *(&a), *(&b));
	return NULL;
}

void *thread2(void *arg) {
	pthread_detach(pthread_self());
	int m=1000, n=2000;
	// for(int i=0; i<10000000; i++) ;
	
	swap(&m, &n);
	printf("M=%d, N=%d\n", *(&m), *(&n));
	return NULL;
}


int main() {
	int x=10, y=20;
	if (pthread_create(&tid1, NULL, thread1, NULL) != 0) {
		exit(1);
	}
	if (pthread_create(&tid2, NULL, thread2, NULL) != 0) {
		exit(1);
	}
	
	for(int i=0; i<1000000; i++) ;
	
	swap(&x, &y);
	printf("X=%d, Y=%d\n", *(&x), *(&y));
	
	for(int i=0; i<10000000; i++) ;
    
    return EXIT_SUCCESS;
}