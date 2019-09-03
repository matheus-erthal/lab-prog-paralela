#include <stdio.h>
#include <omp.h>

void main(){
	#pragma omp parallel
	{
		int ID = 0;
		int np = omp_get_num_threads();
		int iam = omp_get_thread_num();
		printf("Olá da thread %d - total: %d\n", iam, np);
	}
}