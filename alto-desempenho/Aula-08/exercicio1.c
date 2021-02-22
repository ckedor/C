#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define n 10

typedef struct {int a; int *proximo;} tipo_lista;

tipo_lista *lista;
tipo_lista *lista_first;

void inicia(int size)
{
	int i;
	tipo_lista *lista_anterior;
	lista = (tipo_lista *) malloc(sizeof(tipo_lista));
	lista->a = 1; 
	lista_first = lista; 

	for(i = 1; i < size; i++){ 
		lista_anterior = lista;
		lista = (tipo_lista *) malloc(sizeof(tipo_lista));
		lista->a = (i%5)+400;
		lista_anterior->proximo = (int *)lista;
	}

	lista->proximo = (int *) 0; 
} 



int main()
{  
    int a[400][400];
    int b;
	tipo_lista *prox;
	inicia(n);
    b=0; 
	prox = lista_first;

    clock_t start, end;
    double cpu_time_used;
	start = clock();

    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            while(prox){
                lista = prox;
                #pragma omp task firstprivate(lista)
                {
                    int x=0;
                    printf("%d \n",lista->a);
                    int a[400][400] = {};
                    for (int i=1;i<400;i++){
                        for (int j=0;j<400;j++){
                            for (int k=0;k<lista->a;k++){
                                x=x*2+1;
                                a[i][j]=x+i*2+j*3;
                            }
                        }
                    }
                    #pragma omp critical
                    {
                        b=(b+a[399][399])%400;
                    }
                }
                prox = (tipo_lista*)lista->proximo;
            }
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf ("Tempo total: %f \n",cpu_time_used);
        
    printf("b=%d\n",b);
	printf("FIM MAIN\n");
}
