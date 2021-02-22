#include <stdio.h>
#define size 1000

double a[size][size],b[size][size],c[size][size];

void main()
{  
	int i,j;

	//Inicializa as matrizes
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++){
			a[i][j] = 1.5;
			b[i][j] = 2.6;
    	}

	// Fim da inicializacao, soma de a com b
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			c[i][j] = a[i][j] + b[i][j];

	printf("c[0][0]=%.2f   c[15][20]=%.2f  c[size-1][size-1]=%.2f \n",c[0][0],c[15][20],c[size-1][size-1]);
}
