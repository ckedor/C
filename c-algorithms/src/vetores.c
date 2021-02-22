#include <stdio.h>
#include <stdlib.h>
#include "..\inc\vetores.h"

int Vetores_iBusca(int x, int v[], int n) {
	int k;
	for (k = n - 1; k > -1; k--)
		if (v[k] == x) return k;
	return -1;
}

int Vetores_iRemove(int k, int v[], int n) {
	int j;
	for (j = k; k < n - 1; j++)
		v[j] = v[j + 1];
	return n - 1;
}

int Vetores_iInsere(int k, int y, int v[], int n) {
	int j;
	for (j = n; j > k; j--)
		v[j] = v[j - 1];
	v[k] = y;
	return n + 1;
}

int Vetores_iRemoveZeros(int v[], int n) {
	int i = 0, j;
	for (j = 0; j < n; j++) {
		if (v[j] != 0) {
			v[i] = v[j];
			i++;
		}
	}
	return i;
}