// Aula 06 - Ex1

#include <stdio.h>
#include <sys/time.h>
#include "mede_time.h"

#define SIZE 1000
int i,j,k;
int a[SIZE][SIZE];
int b[SIZE][SIZE];
int c[SIZE][SIZE];
int d[SIZE][SIZE];
int ab[SIZE][SIZE];
int cd[SIZE][SIZE];
int r[SIZE][SIZE];

int main()
{ 

	printf("INICIO\n");
	omp_set_nested(1);  //permite aninhamento de paralelismo
	omp_set_num_threads(2);


	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			a[i][j] = (i*3+j*2)%SIZE;
			b[i][j] = (i*4+j*2)%SIZE;
			c[i][j] = (i*5+j*3)%SIZE;
			d[i][j] = (i*2+j*4)%SIZE;
			ab[i][j] = 0;
			cd[i][j] = 0;
			r[i][j] = 0;
		}
	}

    TIMER_CLEAR;
    TIMER_START; 

	#pragma omp parallel sections
	{
  		#pragma omp section
		{ 
            #pragma omp parallel for num_threads(2) private(i,j,k)
			for(i = 0; i < SIZE; i++) {
		        for (k = 0; k < SIZE; k++) 
		            for (j = 0; j < SIZE; j++)
		    		    ab[i][j] = ab[i][j] + a[i][k] * b[k][j];
	        }

			printf("FIM secao 1 - THREAD: %d\n",omp_get_thread_num());
			fflush(stdout);
		}

		#pragma omp section
		{
            #pragma omp parallel for num_threads(2) private(i,j,k)
			for(i = 0; i < SIZE; i++) {
		        for (k = 0; k < SIZE; k++) 
		    	    for (j = 0; j < SIZE; j++)
		    		    cd[i][j] = cd[i][j] + c[i][k] * d[k][j];
	        }

			printf("FIM secao 2 - THREAD: %d\n",omp_get_thread_num());
			fflush(stdout);
		}

	}
	printf("FIM\n");
        
    #pragma omp parallel for num_threads(2) private(i,j)
	for(i = 0; i < SIZE; i++)
	    for(j = 0; j < SIZE; j++)
			r[i][j] = ab[i][j] + cd[i][j];

	printf("r[0][0] = %d\n",r[0][0]);
	printf("r[0][0] = %d\n",r[10][10]);
	printf("r[999][999] = %d\n",r[999][999]);


	TIMER_STOP;
	printf ("Tempo de execucao: %12.7f \n",TIMER_ELAPSED);

	return 0;
}
