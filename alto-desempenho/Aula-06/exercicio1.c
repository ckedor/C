#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#include "mede_time.h"

int SIZE;
double a[1000][1000];
void IniciaMatrizA()
{   
  int i,j;
  #pragma omp parallel num_threads(2) shared(a) private(i,j)
  {
    #pragma omp for
    for(i = 0; i < SIZE; i++){  
      for (j = 0; j < SIZE; j++){
        a[i][j] = (3*i - j)/2;
      }
    }
  }
}

double Soma()
{   
    int i,j;
    double soma = 0;
  
    #pragma omp parallel num_threads(2) shared(a) private(i,j) reduction(+,soma)
	  {
      #pragma omp for 
      for (i = 0; i < SIZE; i++){
          for (j=0; j < SIZE; j++){
              soma = soma + a[i][j];
          }
      }
      printf("\nThread %d - Soma: %f\n", omp_get_thread_num(), soma);
    }
    return soma;
}

int main()
{
    SIZE = 1000;
    TIMER_CLEAR;
    TIMER_START; 
    IniciaMatrizA();
    double soma = Soma();
    TIMER_STOP;
    printf ("\n\n");
    printf ("TEMPO [%d]: %12.7f\n",SIZE,TIMER_ELAPSED);
    printf ("Resultado da soma: %f\n\n", soma);

}