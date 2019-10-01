#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// nowait serve para quebrar a barreira implicita e executar a instrução seguinte
// atomic serve de forma similar a um lock
// schedule - static, dynamic, guided, runtime
// static - iterações do mesmo tamanho e mesma divisao
// dynamic - iterações do mesmo tamanho, divisão por velocidade(quem termina pega mais)
// guided - iterações de tamanho vartiável, dependendo de quanto falta

long fatorial(int number, int chunk_size){
	long fat = 1;
	#pragma omp parallel
	{
		long omp_priv = 1;
		#pragma omp for nowait schedule(dynamic, chunk_size)
		for(int n=2; n <= number; n++)
			omp_priv *= n;
		#pragma omp atomic
		fat *= omp_priv;
	}
	return fat;
}


int main(int argc, char const *argv[]){
	
	omp_set_num_threads(4);

	char *p;

	int tamanho_fat = strtol(argv[argc-1], &p, 10);

	clock_t tempo;
	
	int i;

	for(i = 2; i <= 5; i++){
		tempo = clock();

		long teste = fatorial(tamanho_fat, i);

		printf("chunk_size: %d, resultado: %li\n", i, teste);

		printf("Tempo de execução: %f\n",(clock() - tempo) / (double)CLOCKS_PER_SEC);
	}

	return 0;
}