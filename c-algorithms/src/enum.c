/* Algoritmos de enumeração/Listagem */

#include <stdio.h>
#include <stdlib.h>
#include "..\inc\enum.h"

void SubseqLex(int n) {
	int* s, k;
	s = malloc((n + 1) * sizeof(int));
	s[0] = 0; k = 0;
	while (1) {
		if (s[k] < n) {
			s[k + 1] = s[k] + 1;
			k += 1;
		}
		else {
			s[k - 1] += 1;
			k -= 1;
		}
		if (k == 0) break;
		for (int j = 0; j <= k; j++)
			printf("%d", s[j]);
		printf("\n");
	}
	free(s);
}