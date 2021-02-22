#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#include "mede_time.h"

int SIZE;
double a[1000][1000];
int numThreads;

void IniciaMatrizA()
{   
  int i,j;
  #pragma omp parallel num_threads(numThreads) shared(a) private(i,j)
  {
    #pragma omp for
    for(i = 0; i < SIZE; i++){  
      for (j = 0; j < SIZE; j++){
        a[i][j] = (2*i - j)%1000;
      }
    }
  }
}

double NumOcorrencias(double elemento)
{   
    int i,j;
    double ocorrencias = 0;

    #pragma omp parallel num_threads(numThreads) shared(a) private(i,j) reduction(+:ocorrencias)
	  {
        #pragma omp for 
        for (i = 0; i < SIZE; i++){
          for (j=0; j < SIZE; j++){
              if (a[i][j] == elemento){
                  ocorrencias = ocorrencias + 1;
              }
          }
        }
        printf("\nThread %d - Ocorrencias: %lf\n", omp_get_thread_num(), ocorrencias);
            
    }
    return ocorrencias;
}

int main()
{
    SIZE = 1000;
    numThreads = 4;
    double elemento;
    printf("Elemento da busca: ");
    scanf("%lf",&elemento);
    printf("\n");
    
    TIMER_CLEAR;
    TIMER_START; 
    IniciaMatrizA();
    double numOcorrencias = NumOcorrencias(elemento);

    TIMER_STOP;
    printf ("\nTEMPO [%d]: %12.7f\n",SIZE,TIMER_ELAPSED);
    printf ("Numero de threads: %d\n", numThreads);

    printf ("\nNumero de ocorrencias de %f na matriz: %f\n", elemento, numOcorrencias);

}