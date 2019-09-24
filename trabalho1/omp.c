#include <string.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(){

	clock_t tempo;
	tempo = clock();

	omp_set_num_threads(4);

	int N = 100;

	int i, j, k;

	int matriz_a[N][N], matriz_b[N][N], matriz_c[N][N];

	#pragma omp parallel
	{	
		#pragma omp for
		for(i = 0; i < N; i++){
			for(j = 0; j < N; j++){
				matriz_a[i][j] = 1;
				matriz_b[i][j] = 1;
				matriz_c[i][j] = 0;
			}
		}
	}

	#pragma omp parallel private(i, j, k)
	{	
		#pragma omp for
		for(i = 0; i < N; i++){
			for(j = 0; j < N; j++){
				for(k = 0; k < N; k++){
					matriz_c[i][j] = matriz_c[i][j] + matriz_a[i][j] * matriz_b[i][j];
				}
			}
		}
	}
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("%d ", matriz_c[i][j]);
		}
		printf("\n");
	}
	printf("Tempo de execução: %f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
}