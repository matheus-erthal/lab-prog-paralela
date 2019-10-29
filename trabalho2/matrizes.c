#include <string.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

// gcc-9 -o prog prog.c -fopenmp
// omp_set_num_threads(4);

void soma_matriz(int n, int (*m1)[n], int (*m2)[n], int (*mr)[n]){
	int i, j;
	#pragma omp parallel private(i, j)
	{
		#pragma omp for
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				mr[i][j] = m1[i][j] + m2[i][j];
			}
		}
	}
}

void multiplica_matriz(int n, int (*m1)[n], int (*m2)[n], int (*mr)[n]){
	int i, j, k;
	#pragma omp parallel private(i, j, k)
	{
		#pragma omp for
		for(i = 0; i < n; i++){
			for(j = 0; j < n; j++){
				for(k = 0; k < n; k++){
					mr[i][j] = mr[i][j] + m1[k][j] * m2[i][k];
				}
			}
		}
	}
}

int main(){

	clock_t tempo;
	tempo = clock();

	omp_set_num_threads(4);

	int N = 100;

	int i, j, k;

	int matriz_a[N][N], matriz_b[N][N], matriz_c[N][N], matriz_d[N][N];
	int matriz_e[N][N], matriz_f[N][N], matriz_g[N][N], matriz_h[N][N];
	int matriz_rab[N][N], matriz_rcd[N][N], matriz_ref[N][N], matriz_rgh[N][N];

	#pragma omp parallel private(i, j)
	{	
		#pragma omp for
		for(i = 0; i < N; i++){
			for(j = 0; j < N; j++){
				matriz_a[i][j] = i % 2;
				matriz_b[i][j] = j % 2;
				matriz_c[i][j] = i % 3;
				matriz_d[i][j] = j % 3;
				matriz_e[i][j] = i % 2;
				matriz_f[i][j] = j % 2;
				matriz_g[i][j] = i % 3;
				matriz_h[i][j] = j % 3;
				matriz_rab[i][j] = 0;
				matriz_rcd[i][j] = 0;
				matriz_ref[i][j] = 0;
				matriz_rgh[i][j] = 0;
			}
		}
	}

	#pragma omp parallel sections
    {
		#pragma omp section
		{
			multiplica_matriz(N, matriz_a, matriz_b, matriz_rab);
		} 
		#pragma omp section
		{
			multiplica_matriz(N, matriz_c, matriz_d, matriz_rcd);
		} 
		#pragma omp section
		{
			soma_matriz(N, matriz_e, matriz_f, matriz_ref);
		} 
		#pragma omp section
		{
			soma_matriz(N, matriz_g, matriz_h, matriz_rgh);
		} 
    }

	printf("A x B - multiplicação\n");
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("%d ", matriz_rab[i][j]);
		}
		printf("\n");
	}
	printf("C x D - multiplicação\n");
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("%d ", matriz_rcd[i][j]);
		}
		printf("\n");
	}
	printf("E x F - soma\n");
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("%d ", matriz_ref[i][j]);
		}
		printf("\n");
	}
	printf("G x H - soma\n");
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("%d ", matriz_rgh[i][j]);
		}
		printf("\n");
	}

	printf("Tempo de execução: %f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
}