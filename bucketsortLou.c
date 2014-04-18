#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funzioniordinamento.h"

int main(int v, char **c){

	//srand(( unsigned )time(NULL));

	inputCorretto(v, c);

	char ch;
	double *a;
	int len = atoi(c[2]);

	fprintf(stdout, "Vuoi generare l'array a random (y/n)? ");
	fscanf(stdin, "%c", &ch);
	if( ch == 'y'){
		a = generateArray(RANDOM, DOUBLE, len, 100);
		for( int i = 0; i<len; i++)
			a[i] = a[i]/100;
	}
	else
		a = generateArray(NOTRANDOM, DOUBLE, len);

	printArray(a, len, "double");

	bucketSort( a, len );

	return 0;
}