// Soma dos elementos de uma matriz usando MPI_Scatter para distribuir os dados.
// Numero de elementos do vetor: multiplo do numero de processos

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

double a[1000][1000];

int main(int argc, char *argv[])
{
	int	n,n_nos, rank;
	int i,j,k;
	double max,max_final,max_parcial;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
	n = 1000;

	printf("INICIO\n");
	fflush(stdout);

	k = n/n_nos;

	if (rank == 0){
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				a[i][j] = rand()%1000;
	}              

//================= Divisao do vetor para todos os ranks ======================
	// Todos os ranks executam a chamada Scatter e recebem parte da matriz do rank 0
	// OBS: Scatter nao possui TAG nem destino, apenas a fonte que no caso eh 0
	MPI_Scatter(a,k*n,MPI_DOUBLE,a,k*n,MPI_DOUBLE,0,MPI_COMM_WORLD);
//==============================================================================

// ============== Calculo da soma parcial em cada rank =========================
	max_parcial = 0;
        
	for(i = 0; i < k; i++){
		for(j = 0; j < n; j++){
			if (max_parcial < a[i][j]);
                max_parcial = a[i][j];
        }
    }

	printf("rank=%d max_parcial=%f\n",rank,max_parcial);
	fflush(stdout);
//============================================================================= 

//================= Recepcao das somas parciais no rank 0 ===================== 
	if (rank == 0){
		max_final = max_parcial;
		
		for(i = 1; i < n_nos; i++){
			MPI_Recv(&max,1,MPI_DOUBLE,MPI_ANY_SOURCE,11,MPI_COMM_WORLD,&status);
			if (max > max_final)
                max_final = max;
		}

		printf("RESULTADO=%f\n", max_final);
		fflush(stdout); 
	}

	else
		MPI_Send(&max_parcial,1,MPI_DOUBLE,0,11,MPI_COMM_WORLD);
//============================================================================= 
             
	MPI_Finalize();
	return 0;
}