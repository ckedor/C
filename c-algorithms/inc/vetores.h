#include <stdio.h>
#include <stdlib.h>

/* ---------------------------------------------------------- *\
   Recebe um inteiro x, um vetor de tamanho n e devolve k tal 
   que v[k] == x. Retorna -1 se x não está no vetor.        
\* ---------------------------------------------------------- */
int Vetores_iBusca(int x, int v[], int n);

/* ---------------------------------------------------------- *\
   Remove o elemento k do vetor v[] e devolve 
   o novo valor de n. A função supõe 0 <= k < n.
\* ---------------------------------------------------------- */
int Vetores_iRemove(int k, int v[], int n);

/* ---------------------------------------------------------- *\
   Insere o elemento y na posição k e devolve
   n + 1. A função supõe 0 <= k <= n
\* ---------------------------------------------------------- */
int Vetores_iInsere(int k, int y, int v[], int n);

/* ---------------------------------------------------------- *\
   Remove todos os elementos nulos de v[] e 
   devolve o novo tamanho de v[] 
\* ---------------------------------------------------------- */
int Vetores_iRemoveZeros(int v[], int n);