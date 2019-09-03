#include <string.h>
#include <stdio.h>
#include <omp.h>

#define N 10000

// gcc -o prog prog.c -fopenmp
// omp_set_num_threads(4);

int main(){
	float a[N], b[N];
	int i, n;
	float temp, csum;
	n = 10;
	csum = 0.0;
	for(i = 0; i < 10; i++){
		a[i] = 1;
		b[i] = 1;	
	}
	// shared: o valor global é visível a todos
	// private: o valor é inicializado aleatoriamente em todas as threads
	// first private: o valor final é o valor inicial, e em cada thread é inicializado como o valor inicial
	// last private: o valor final é o valor da última thread a ser executada
	// reduction: combina os valores de todas as threads a partir de uma operação sobre eles(não recebe funções)

	// omp parallel: replica o trabalho
	// omp for: divide o trabalho, paralelismo de dados, procedimentos iguais
	// omp sections: divide o trabalho, paralelismo funcional, procedimentos diferentes
	#pragma omp parallel shared(a, b, n) private(temp, i) reduction(+:csum)
	{
		#pragma omp for
		for(i=0; i < n; i++){
			temp = a[i] + b[i];
			csum += temp+1;
		}
	}
	printf("%f\n", csum);
}