#include <stdio.h>
#include <stdlib.h>

/*nó arvore binaria*/
typedef struct {
	int conteudo;
	struct no* esq;
	struct no* dir;
}stBinaryTreeCel;

typedef stBinaryTreeCel* stArvore;

/* ---------------------------------------------------------- *\
   Varredura ERD (Esquerda-Raiz-Direita) de árvore binária
\* ---------------------------------------------------------- */
void BinaryTreeErd(stArvore r);



/*Exemplos*/
//void ExemploVarreduraBinaryTree();