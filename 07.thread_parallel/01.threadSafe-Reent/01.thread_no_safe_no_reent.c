#include <stdio.h>
#include <stdlib.h>

int t;

void swap(int *x, int *y) {
	t = *x;
	*x = *y;
	// `my_func()` could be called here
	*y = t;
}

int main() {
	int x=10, y=20;
	swap(&x, &y);
	printf("X=%d, Y=%d\n", *(&x), *(&y));
    
    return EXIT_SUCCESS;
}