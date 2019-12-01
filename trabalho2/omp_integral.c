#include <stdio.h>
#include <omp.h>
#include <time.h> 

void main(int argc, char** argv) {

    omp_set_num_threads(5);

    int my_rank;
    int num_processos;
    float a=0.0, b=1.0;
    int num_trap=1024;
    float h;
    float local_a, local_b;
    int local_n;
    double integral;
    float total;
    int source;
    int dest=0;
    int tag=200;
    float calcula(float local_a, float local_b, int local_n, float h);
    int resto;
        clock_t t; 
    t = clock(); 
    
    h = (b-a) / num_trap;
    
    integral = 0;
    
    // soma os valores associados
    #pragma omp parallel for reduction(+:integral)
    for(int i=1; i < num_trap; i++) {
        integral += (i/(double)num_trap)*(i/(double)num_trap);
    }
    integral = integral * 1.0/num_trap;
    integral += 1.0/(2*num_trap);
    
    total = integral;
    printf("Valor da integral: %f\n", total);
            t = clock() - t; 
        double tempo = ((double)t)/CLOCKS_PER_SEC;
        printf("gastou %f segundos\n", tempo);
}


float calcula(float local_a, float local_b, int local_n, float h) {
    float integral;
    float x;
    float f(float x);
    int i;
    integral = 0;
    x = 0;
    
    return integral;
}