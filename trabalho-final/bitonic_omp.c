#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) > (B)) ? (B) : (A))
#define UP 0
#define DOWN 1

void bitonic_sort_seq(int start, int length, int *seq, int flag);
void bitonic_sort_par(int start, int length, int *seq, int flag);
void swap(int *a, int *b);

int m;

int main(void){
    int i, j;
    int n;
    int inicio, fim;
    int flag;
    int *seq;

    double startTime, elapsedTime; /* for checking/testing timing */
    double clockZero = 0.0;

    int numThreads,id;

    printf("Insira a quantidade de chaves, sendo uma potência de 2(sugestão: 1024): ");
    scanf("%d", &n);

    seq = (int *) malloc (n * sizeof(int));

    printf("Insira um intervalo para geração dos números pseudo-aleatórios(formato: inicio fim): ");
    scanf("%d %d", &inicio, &fim);
    srand(time(NULL));
    for (i = 0; i < n; i++){
        seq[i] = (rand() % (inicio - fim)) + (inicio+1);
    }

    // start
    // startTime = walltime( &clockZero );

    numThreads =  omp_get_max_threads();

    printf("Utilizando: %d threads\n", numThreads);

    // making sure input is okay
    if ( n < numThreads * 2 )
    {
        printf("O número de chaves é menor que 2 * número de processos.\n");
        exit(0);
    }

    // the size of sub part
    m = n / numThreads;

    // make the sequence bitonic - part 1
    for (i = 2; i <= m; i = 2 * i)
    {
        #pragma omp parallel for shared(i, seq) private(j, flag)
        for (j = 0; j < n; j += i)
        {
            if ((j / i) % 2 == 0)
                flag = UP;
            else
                flag = DOWN;
            bitonic_sort_seq(j, i, seq, flag);
        }
    }

    // make the sequence bitonic - part 2
    for (i = 2; i <= numThreads; i = 2 * i)
    {
        for (j = 0; j < numThreads; j += i)
        {
            if ((j / i) % 2 == 0)
                flag = UP;
            else
                flag = DOWN;
            bitonic_sort_par(j*m, i*m, seq, flag);
        }
        #pragma omp parallel for shared(j)
        for (j = 0; j < numThreads; j++)
        {
            if (j < i)
                flag = UP;
            else
                flag = DOWN;
            bitonic_sort_seq(j*m, m, seq, flag);
        }
    }

    // bitonic sort
    //bitonic_sort_par(0, n, seq, UP);
    //bitonic_sort_seq(0, n, seq, UP);

    //end
    // elapsedTime = walltime( &startTime );

    /*
    // print a sequence
    for (i = 0; i < n; i++){
      printf("%d ", seq[i]);
    }
    printf("\n");
    */

    printf("Tempo decorrido = %.2f segundos.\n", elapsedTime);

    for(i = 0; i < n; i++){
        printf("%d ", seq[i]);
    }
    printf("\n");

    free(seq);
}

void bitonic_sort_seq(int start, int length, int *seq, int flag){
    int i;
    int split_length;

    if (length == 1)
        return;

    if (length % 2 !=0 )
    {
        printf("error\n");
        exit(0);
    }

    split_length = length / 2;

    // bitonic split
    for (i = start; i < start + split_length; i++)
    {
        if (flag == UP)
        {
            if (seq[i] > seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
        else
        {
            if (seq[i] < seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
    }

    bitonic_sort_seq(start, split_length, seq, flag);
    bitonic_sort_seq(start + split_length, split_length, seq, flag);
}

void bitonic_sort_par(int start, int length, int *seq, int flag){
    int i;
    int split_length;

    if (length == 1)
        return;

    if (length % 2 !=0 )
    {
        printf("The length of a (sub)sequence is not divided by 2.\n");
        exit(0);
    }

    split_length = length / 2;

    // bitonic split
    #pragma omp parallel for shared(seq, flag, start, split_length) private(i)
    for (i = start; i < start + split_length; i++)
    {
        if (flag == UP)
        {
            if (seq[i] > seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
        else
        {
            if (seq[i] < seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
    }

    if (split_length > m)
    {
        // m is the size of sub part-> n/numThreads
        bitonic_sort_par(start, split_length, seq, flag);
        bitonic_sort_par(start + split_length, split_length, seq, flag);
    }

    return;
}

void swap(int *a, int *b){
    int t;
    t = *a;
    *a = *b;
    *b = t;
}