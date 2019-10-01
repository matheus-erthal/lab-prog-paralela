#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// diretiva section - separa o codigo em threads diferentes
// default - especifica o que acontece com variáveis não listadas

#define SIZE 10

int main(int argc, char const *argv[]){
	
	omp_set_num_threads(4);

	int i, j, k;

	int n = SIZE;

	int a[SIZE][SIZE], b[SIZE][SIZE], c[SIZE][SIZE], d[SIZE][SIZE];
	int e[SIZE][SIZE], f[SIZE][SIZE], g[SIZE][SIZE], h[SIZE][SIZE];
	int r1[SIZE][SIZE], r2[SIZE][SIZE], r3[SIZE][SIZE], r4[SIZE][SIZE];
	int r[SIZE][SIZE];

	// inicializa matrizes
	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			a[i][j] = 1;
			b[i][j] = 1;
			c[i][j] = 1;
			d[i][j] = 1;
			e[i][j] = 1;
			f[i][j] = 1;
			g[i][j] = 1;
			h[i][j] = 1;
			r[i][j] = 0;
			r1[i][j] = 0;
			r2[i][j] = 0;
			r3[i][j] = 0;
			r4[i][j] = 0;	
		}
	}

	#pragma omp parallel shared(n, a, b, c, d, e, f, g, h, r) private(i, j, k)
	{
		#pragma omp sections private(r1, r2, r3, r4) nowait
		{
			#pragma omp section
			{
				// r1 = a + b
			}
			#pragma omp section
			{
				#pragma omp parallel private(i, j, k)
				{	
					#pragma omp for
					for(i = 0; i < n; i++){
						for(j = 0; j < n; j++){
							for(k = 0; k < n; k++){
								r2[i][j] = r2[i][j] + c[k][j] * d[i][k];
							}
						}
					}
				}
				#pragma omp critical
				{
					for(i = 0; i < n; i++){
						for(j = 0; j < n; j++){
							r[i][j] += r2[i][j];
						}
					}
				}
				// r2 = c * d
			}
			#pragma omp section
			{
				// r3 = e + f
			}
			#pragma omp section
			{	
				// #pragma omp parallel private(i, j, k)
				// {	
				// 	#pragma omp for
				// 	for(i = 0; i < n; i++){
				// 		for(j = 0; j < n; j++){
				// 			for(k = 0; k < n; k++){
				// 				r4[i][j] = r4[i][j] + g[k][j] * h[i][k];
				// 			}
				// 		}
				// 	}
				// }
				// r4 = g * h
			}
		}
	}

	printf("Matriz Resultado:\n");
	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			printf("%d ", r[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}