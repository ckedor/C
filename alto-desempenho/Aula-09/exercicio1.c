#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int	n,n_nos, rank;
	MPI_Status	status;
	int inicio,vetor[20],i,k;
    int maior_parcial, maior_total, maior;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
	n = 20;
	k = n / n_nos;
	inicio = rank * k;

//================= Divisao do vetor para todos os ranks ======================
    if (rank == 0){
        printf ("Vetor Inicial - ");
		for(i = inicio; i < n; i++){
			vetor[i] = rand()%20;
            printf (" %d", vetor[i]);
        }
        printf ("\n");
        fflush(stdout);
        for (i = 1; i < n_nos; i++){
            MPI_Send(&vetor[k*i],k,MPI_INT,i,10,MPI_COMM_WORLD);
            printf("\n");
        }
    }
    else {
        MPI_Recv(vetor,k,MPI_INT,0,10,MPI_COMM_WORLD,&status);
        fflush(stdout);
    }
//=============================================================================


//================== Calculo do maior em cada rank ============================
	maior_parcial = 0;
    printf ("rank=%d - ", rank);
	for(i = 0; i < k; i++) 
    {   
        printf (" %d", vetor[i]);
        if (vetor[i] > maior_parcial){
		    maior_parcial = vetor[i];
        }
    }

	printf("\nrank=%d - maior_parcial=%d\n",rank,maior_parcial);
	printf("\n");
    fflush(stdout);
//=============================================================================

//================= Recepcao dos maiores parciais no rank 0 =====================
	if (rank == 0){
		maior_total = 0;
          
		for(i = 1; i < n_nos; i++){
			MPI_Recv(&maior,1,MPI_INT,MPI_ANY_SOURCE,11,MPI_COMM_WORLD,&status);
			if (maior > maior_total)
                maior_total = maior;
		}
           
		printf("RESULTADO=%d\n", maior_total);
		fflush(stdout); 
	}

	else
		MPI_Send(&maior_parcial,1,MPI_INT,0,11,MPI_COMM_WORLD);
//=============================================================================
    
    MPI_Finalize();
	return 0;

}