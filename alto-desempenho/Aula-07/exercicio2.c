#include <semaphore.h>
#include <stdio.h>
#include <sys/time.h>
#include "mede_time.h"
sem_t sem;
sem_t sem2;

#define size 20000
int A[size],B[size],C[size];

int main()
{
    TIMER_CLEAR;
    TIMER_START;

    sem_init(&sem,0,0);
    sem_init(&sem2,0,0);

    #pragma omp parallel sections
	{
		#pragma omp section
		{
            int i,j;
            A[0]=15;
    	    for (i=1;i<size;i++) {
                for(j=0;j<size;j++){
      			    A[i]=(A[i-1]+i*3+15+j)%1000;
                }
                sem_post(&sem);
            }
        }
        #pragma omp section
		{
            int i,j;
            B[0] = 1; 
    	    for(i = 1; i < size; i++){
                sem_wait(&sem);
                for(j=0;j<size;j++){
				    B[i] = (B[i-1]*3 + A[i-1]+j)%1000;
                }
                sem_post(&sem2);
            }
        }
        #pragma omp section
		{
            int i,j;
            C[0] = 1; 
		    for(i = 1; i < size; i++){
		    	sem_wait(&sem2);
                for(j=0;j<size;j++){
                    C[i] = (C[i-1] + B[i-1] * 2+j)%1000;
                }
			    
            }
        }
    }
    sem_destroy(&sem);
    sem_destroy(&sem2);

    printf("C[0]=%d  C[1]=%d  C[%d]=%d\n",C[0],C[1],(size-1),C[size-1]);  
	fflush(stdout);
	printf("FIM\n");

    TIMER_STOP;
    printf ("Tempo de execucao: %12.7f \n",TIMER_ELAPSED);
}