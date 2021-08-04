#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
	int x;
	int y;
} thread_args;

void swap(int *x, int *y) {
	int t;
	t = *x;
	*x = *y;
	
	for(int i=0; i<1000000; i++) ;
/* while performing for loop, there might be an task switching between threads */
	*y = t;
}

pthread_t	tid1, tid2;	/* thread ID */
void *thread(void *_arg) {
	pthread_detach(pthread_self());
	
	thread_args *args = (thread_args *)_arg;
	int a=args->x;
	int b=args->y;
	
	swap(&a, &b);
	printf("A=%d, B=%d\n", *(&a), *(&b));
	return NULL;
}

int main() {
	
	int x=10, y=20;
	thread_args arg;
	
	arg.x=100;
	arg.y=200;

	if (pthread_create(&tid1, NULL, thread, &arg) != 0) {
		exit(1);
	}
	
	arg.x=1000;
	arg.y=2000;
	if (pthread_create(&tid2, NULL, thread, &arg) != 0) {
		exit(1);
	}
	
	
	for(int i=0; i<1000000; i++) ;
	
	swap(&x, &y);
	printf("X=%d, Y=%d\n", *(&x), *(&y));
	
	for(int i=0; i<10000000; i++) ;
    
    return EXIT_SUCCESS;
}