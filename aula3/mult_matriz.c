#include <string.h>
#include <stdio.h>
#include <omp.h>

int main(){

	int N = 1000;

	int i, j, k;

	int matriz_a[N][N], matriz_b[N][N], matriz_c[N][N];

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			matriz_a[i][j] = 1;
			matriz_b[i][j] = 1;
		}
	}

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			matriz_c[i][j] = 0;
			for(k = 0; k < N; k++){
				matriz_c[i][j] = matriz_c[i][j] + matriz_a[i][j] * matriz_b[i][j];
			}
			printf("%d\n", matriz_c[i][j]);
		}
	}
	
}