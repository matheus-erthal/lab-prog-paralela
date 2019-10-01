#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// diretiva section - separa o codigo em threads diferentes

#define SIZE 10

int main(int argc, char const *argv[]){
	
	omp_set_num_threads(4);

	int i, j;

	int n = SIZE;

	int a[SIZE], b[SIZE], c[SIZE], d[SIZE];

	for(i = 0; i < SIZE; i++){
			a[i] = i % 3 + 1;
			b[i] = i % 3 + 1;
			c[i] = i % 3 + 1;
			d[i] = i % 3 + 1;
	}

	#pragma omp parallel shared(n, a, b, c, d) private(i)
	{
		#pragma omp sections nowait
		{
			#pragma omp section
			for(i = 0; i < n-1; i++)
				b[i] = (a[i] + a[i+1] / 2);
			#pragma omp section
			for(i = 0; i < n; i++)
				d[i] = 1.0/c[i];
		}
	}

	printf("Vetor A:\n");
	for(i = 0; i < SIZE; i++){
		printf("%d ", a[i]);
	}
	printf("\n");

	printf("Vetor B:\n");
	for(i = 0; i < SIZE; i++){
		printf("%d ", b[i]);
	}
	printf("\n");

	printf("Vetor C:\n");
	for(i = 0; i < SIZE; i++){
		printf("%d ", c[i]);
	}
	printf("\n");

	printf("Vetor D:\n");
	for(i = 0; i < SIZE; i++){
		printf("%d ", d[i]);
	}
	printf("\n");

	return 0;
}