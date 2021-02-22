#include <stdio.h>
#include <stdlib.h>

/*n� arvore binaria*/
typedef struct {
	int conteudo;
	struct no* esq;
	struct no* dir;
}stBinaryTreeCel;

typedef stBinaryTreeCel* stArvore;

/* ---------------------------------------------------------- *\
   Varredura ERD (Esquerda-Raiz-Direita) de �rvore bin�ria
\* ---------------------------------------------------------- */
void BinaryTreeErd(stArvore r);



/*Exemplos*/
//void ExemploVarreduraBinaryTree();