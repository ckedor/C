//programama usando simple lock
//ERRADO: em algumas execuções ocorre travamento
//ERRO: múltiplos locks pela mesma thread sem ter ocorrido unlock.
#include <stdio.h>
#include <omp.h>

int A,B,X,Y;
omp_lock_t sem;

int main()
{ 
	printf("INICIO\n");

	omp_init_lock(&sem);
	omp_set_lock(&sem);
	omp_set_num_threads(2);

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			int i;
			printf("secao 1\n");
    
			for (i = 0; i < 10000; i++){
				printf("a");
				fflush(stdout);
			}
     
			A = 9;
			omp_unset_lock(&sem);

			for (i = 0 ;i < 10; i++){
				printf("b");
				fflush(stdout);
			}

     		B = 15;
			printf("B=%d\n",B);
			fflush(stdout);
			omp_unset_lock(&sem);
		}

		#pragma omp section 	
		{ 
			printf("secao 2\n");
			fflush(stdout);
			omp_set_lock(&sem);
			X = A + 1;
			omp_set_lock(&sem);
			printf("B=%d\n",B);
			fflush(stdout);
			Y = B + 1;
		}
	}
 
	omp_destroy_lock(&sem);
	printf("X=%d    Y=%d \n",X,Y);  //resultado correto: X=10   Y=16
	fflush(stdout);
	printf("FIM\n");
}
