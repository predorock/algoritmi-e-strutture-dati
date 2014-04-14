#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/funzioniordinamento.h"

int main(int v, char** c){

	inputCorretto(v, c);
	int len = atoi(c[1]);
	int cifre = atoi(c[2]);

	int** m;
	m = generateMatrixRadix( len, cifre );

	for( int i = 0; i < len; i++ ){
		printArray(m[i], cifre);
		putchar('\n');
	}

	radixSort(m, len, cifre);

	return 0;
}