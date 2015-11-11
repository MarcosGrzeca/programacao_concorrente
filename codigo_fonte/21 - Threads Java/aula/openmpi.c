#include <omp.h>
#include <stdio.h>

#ifndef T
#define T 10
#endif

int main() {
	int id;
	omp_set_num_threads(T);

	#pragma omp parallel 
	{
		printf("Alo mundo\n");

	}
}