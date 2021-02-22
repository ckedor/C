#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int	n,n_nos, rank;
	MPI_Status	status;
	int inicio,vetor[20],i,k;
    int ocorr_parcial, ocorr_total, ocorr;
    int op;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
	n = 20;
	k = n / n_nos;
	inicio = rank * k;

//================= Divisao do vetor para todos os ranks ======================
    if (rank == 0){

        printf ("Digite um valor: ");
        fflush(stdout);
        scanf("%d", &op);

        printf ("Vetor Inicial - ");
		for(i = inicio; i < n; i++){
			vetor[i] = rand()%4;
            printf (" %d", vetor[i]);
        }
        printf ("\n");
        fflush(stdout);
        for (i = 1; i < n_nos; i++){
            MPI_Send(&vetor[k*i],k,MPI_INT,i,10,MPI_COMM_WORLD);
            MPI_Send(&op,1,MPI_INT,i,11,MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Recv(vetor,k,MPI_INT,0,10,MPI_COMM_WORLD,&status);
        MPI_Recv(&op,1,MPI_INT,0,11,MPI_COMM_WORLD,&status);
        fflush(stdout);
    }
//=============================================================================


//================== Calculo do maior em cada rank ============================
	ocorr_parcial = 0;
    printf ("rank=%d - ", rank);
	for(i = 0; i < k; i++) 
    {   
        printf (" %d", vetor[i]);
        if (vetor[i] == op){
		    ocorr_parcial++;
        }
    }

	printf("\nrank=%d - ocorrencias_parcial=%d\n",rank,ocorr_parcial);
	printf("\n");
    fflush(stdout);
//=============================================================================

//================= Recepcao dos maiores parciais no rank 0 =====================
	if (rank == 0){
		ocorr_total = ocorr_parcial;
          
		for(i = 1; i < n_nos; i++){
			MPI_Recv(&ocorr,1,MPI_INT,MPI_ANY_SOURCE,12,MPI_COMM_WORLD,&status);
			ocorr_total += ocorr;
		}
           
		printf("RESULTADO=%d\n", ocorr_total);
		fflush(stdout); 
	}

	else{
        MPI_Send(&ocorr_parcial,1,MPI_INT,0,12,MPI_COMM_WORLD);
    }
		
//=============================================================================

    MPI_Finalize();
	return 0;

}