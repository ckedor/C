
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>
#include <time.h>


int busca(int *X, int numero)
{
	int i, achou, indice;
	
	i = 0;
	achou = 0;

	while((achou == 0) && (i < 10000)){

		if(X[i] == numero) {	
			achou = 1;
			indice = i;
  		}

		else 
			i = i + 1;
	}   
        
	if(achou == 0) 
		indice = -1;
	
	return(indice);
}

int main(int argc, char *argv[])
{

    int	n,n_nos, rank;
    int  A[10000],B[10000],C[10000],D[10000];
	int indice;
	int vet_indices[4];
    int numero;
    int i;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n_nos);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
    
    if(rank == 0){
        printf("Numero :");
        fflush(stdout);
	    scanf("%d",&numero);
        
	} 

	MPI_Bcast(&numero,1,MPI_INT,0,MPI_COMM_WORLD);
    
    if(rank == 0){
        for(i = 0; i < 1000; i++)
		    A[i] = (rand()%20);
        
        printf("\nA: ");
        fflush(stdout);
        for(i = 0; i < 10; i++)
            printf("%d - ", A[i]);
            fflush(stdout);
        printf("\n");
        fflush(stdout);

        indice = busca(A, numero);
    }

    if(rank == 1){
        for(i = 0; i < 1000; i++)
		    B[i] = (rand()%20);

        indice = busca(B, numero);
    }

    if(rank == 2){
        for(i = 0; i < 1000; i++)
		    C[i] = (rand()%20);

        indice = busca(C, numero);
    }

    if(rank == 3){
        for(i = 0; i < 1000; i++)
		    D[i] = (rand()%20);
        
        indice = busca(D, numero);

    } 

    MPI_Gather(&indice,1,MPI_INT,vet_indices,1,MPI_INT,0,MPI_COMM_WORLD);


    if(rank == 0){
        for (i=0; i<4; i++)
            printf("Vetor[%d]: %d\n", i, vet_indices[i]);
    }


    MPI_Finalize();


}