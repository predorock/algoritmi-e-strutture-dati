#ifndef FUNZIONIORDINAMENTO_H
	#define FUNZIONIORDINAMENTO_H

	//I numeri li genererò a random da 1 a LIMITE
	#define LIMITE 10
	#define RANGERADIX 9
	
	#define RANDOM 4
	#define NOTRANDOM 3

	#define INT 1
	#define DOUBLE 2

	void printArray( void* a, int l );
	//Stampa un array di lunghezza 'len' e di tipo indicato all'interno della funzione

	void printMatrix( int** m, int righe, int colonne);
	//Stampa una matrice

	void printSpace(int n);		
	//Funzione che stampa n spazi

	void printHeap(int array[], int len);
	//Funzione che rappresenta graficamente uno Heap

	int inputCorretto( int v, char** c );	
	//Controlla che hai inserito esattamente 3 argomenti per argv

	int* generaArrayCounting( int len, int g );		
	//Genera array per il COUNTING SORT, quindi con un gap limitato fra min e max.

	void* generateArray( int num, int tipo, int len, ... );	
	//Genera un array di tipo 'tipo' e lunghezza 'len' di numeri randomici o non. Restituisce NULL se gli passi un tipo sbagliato o no implementato.

	int** generateMatrixRadix( int len, int cifre );
	//Genera una matrice contenente degli interi scritti tramite caratteri. Ogni intero sarà rappresentato con 'cifre' cifre.

	int findMax( int* a, int l);		
	//FindMax trova il max in un array

	int findMin( int* a, int l);		
	//FindMin trova il min in un array

	void copiaArray( int* b, int* m, int len );	
	//Copia un array di interi.

	int* countingSort( int* a, int lenA );	
	//CoutingSort

	void buildArray( int* a, int heapsize);		
	//Funzione che usa heapify per costruire uno heap.

	void heapify( int* a, int i, int heapsize );	
	//Heapify.

	void heapsor(int* a, int heapsize);			
	//HeapSort.

	int** radixSort( int** m, int len, int cifre );
	//RadixSort

#endif

//Il generaArray lavora con i varargs, mentre il generaArrayCounting non ancora.