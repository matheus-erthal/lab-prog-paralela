#include <stdio.h>
#include <mpi.h>
#include <time.h> 

int main(int argc, char ** argv) {
    int my_rank;
    int p; 
    float a = 0.0, b = 1.0;
    int n = 1024;
    float h;
    float local_a, local_b;
    int local_n;
    float integral;
    float total;
    int source;
    int dest = 0;
    int tag = 50;
    MPI_Status status;

    clock_t t; 
    t = clock(); 

    float calcula(float local_a, float local_b, int local_n, float h);
    MPI_Init(& argc, & argv);
    MPI_Comm_rank(MPI_COMM_WORLD, & my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, & p);
    h = (b - a) / n;
    local_n = n / p;


    int resto = n%p;
    if(my_rank < resto){
        local_n++;
        local_a = a + my_rank * local_n * h;
    }
    else{
        local_a = a + (resto * (local_n+1) * h) + (my_rank - resto) * local_n * h;
    }


    local_b = local_a + local_n * h;
    integral = calcula(local_a, local_b, local_n, h);

    MPI_Reduce(&integral, &total, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (my_rank == 0){
        printf("Resultado : % f\n", total);
        t = clock() - t; 
        double tempo = ((double)t)/CLOCKS_PER_SEC;
        printf("gastou %f segundos\n", tempo);
    }
    
    MPI_Finalize();
}

float calcula(float local_a, float local_b, int local_n, float h) {
    float integral;
    float x,
    i;
    float f(float x);
    integral = (f(local_a) + f(local_b)) / 2.0;
    x = local_a;
    for (i = 1; i <= local_n; i ++) {
        x += h;
        integral += f(x);
    }
    integral *= h;
    return integral;
}

float f(float x) {
    float fx;
    fx = x * x;
    return fx;
}