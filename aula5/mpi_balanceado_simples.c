#include <stdio.h>
#include <string.h>
#include <mpi.h>

// mpicc primeiro_mpi.c -o mpi.exe
// mpirun --hostfile hostfile -np 15 mpi.exe
// export OMPI_MCA_btl=self,tcp

int main(int argc, char** argv){
    int meu_rank, np, origem, destino, tag=0;
    char msg[100];
    
    int N = 14;

    int matriz_a[N][N], matriz_b[N][N], matriz_c[N][N];

    int i, j, k;

    for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			matriz_a[i][j] = 1;
			matriz_b[i][j] = 1;
		}
	}

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    for(i = (N / np) * meu_rank; i < (N / np) * (meu_rank+1); i++){
        for(j = 0; j < N; j++){
            matriz_c[i][j] = 0;
            for(k = 0; k < N; k++){
                matriz_c[i][j] = matriz_c[i][j] + matriz_a[i][j] * matriz_b[k][j];
            }
        }
    }

    if(meu_rank != 0){
        sprintf(msg, "Processo %d está calculando!", meu_rank);
        destino = 0;
        for(i = (N / np) * meu_rank; i < (N / np) * (meu_rank+1); i++){
            MPI_Send(matriz_c[i], sizeof(int)*N + 1, MPI_INT, destino, tag, MPI_COMM_WORLD);
        }
    }else{
        for(origem=1; origem < np; origem++){
            for(i = (N / np) * origem; i < (N / np) * (origem+1); i++){
                MPI_Recv(matriz_c[i], sizeof(int)*N + 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            }
        }
        for(i = 0; i < N; i++){
            for(j = 0; j < N; j++){
                printf("%d ", matriz_c[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    MPI_Finalize();

    // printf("Teste MPI\n");
    return 0;
}

