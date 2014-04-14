#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdarg.h>
#include <unistd.h>
#include "funzioniordinamento.h"

//Si commenta sempre da sola
void printArray( int* a, int l ){

	for( int i = 0; i < l; i++ )
		fprintf(stdout, "%d ", a[i]);
	putchar('\n');
}

void printMatrix( int** m, int righe, int colonne ){
	for(int i = 0; i < righe; i++){
		for(int j = 0; j < colonne; j++)
			fprintf(stdout, "%d ", m[i][j]);
		putchar('\n');
	}
}

void printSpace(int n){
	for(int i = 0;i < n;i++)
		printf(" ");
}

void printHeap(int array[], int len){
	//un po di spazi
	printf("\n");
	//numero di elementi che vanno stampati nella riga
	int riga_heap = 1;
	//contatore che mi indica quando devo andare a capo
	int count = riga_heap;
	
	for(int i = 0;i < len; i++){
		//distribuzione delgi spazi prima e dopo(non è perfetta, 
		//ma l'approssimazione grafica mi sembra abbastanza buona)
		printSpace(len/(i+1));
		//stampo l'elemento
		printf("%d",array[i]);
		//ancora spazi
		printSpace(len/(i+1));
		//scalo contore per andare a capo
		count--;
		//se il contatore si esaurisce vado a capo
		if(count == 0){
			//vado a capo
			printf("\n\n");
			//incremento gli elementi da stampare per riga
			riga_heap*=2;
			//ricarico contatore
			count = riga_heap;
		}
	}
	//ancora spazi
	printf("\n\n\n");
}

int inputCorretto( int v, char** c ){

	//Se non inseriamo esattamente 2 argomenti, oltre al nome del file, il programma non prosegue.
	if( v != 3 ){
		fprintf(stderr, "Gli argomenti di argc devono essere 2:\n1) lunghezza array, o matrice\n2) 1/2 di gap fra il min e il max o il numero di cifre di ogni int della matrice.\n");
		return 0;
	}

	//Stampa di debug per controllare i dati in input
	#ifdef DEBUG
		for( int i = 0; i<v; i++ ){
			fprintf(stdout, "%s\n", c[i]);
		}
	#endif

	return 1;
}

int* generaArrayCounting( int len, int g){

	int* a = malloc( len * sizeof(int) );

	a[0] = rand()%LIMITE;
	for( int i = 1; i < len; i++ ){
		a[i] = rand()%LIMITE;
		if( a[i] > a[0] ){
			if( (a[i]-a[0]) >= g )
				i--;
		}
		else if( a[i] < a[0] ){
			if( (a[0]-a[i]) >= g )
				i--;
		}
	}
	return a;
}

void generateArray( int num, int* a, int len, ... ){

	//VARARGS
	va_list arguments;			//Variabile di tipo va_list
	va_start(arguments, len);	//Facciamo iniziare la lista all'argomento len

	char c;
	int range;

	//Se i numeri abbiamo deciso di inserirli randomicamente avremo un 4°
	//argomento in ingresso alla funzione che mi indicherà il range entro
	//il quale devo generare i numeri.
	if( num == RANDOM ){
		c = 'y';			
		range = va_arg(arguments, int);		//Recuperiamo il valore del successivo argomento.
			
		#ifdef DEBUG
			fprintf(stdout, "range: %d", range);
		#endif		
	}

	//Se vogliamo generare i numeri randomicamente
	if( c == 'y'){
		for( int i = 0; i < len; i++ )
			a[i]=rand()%range;
	}
	//Se vogliamo inserire noi i numeri a mano
	else{
		int tmp;
		for( int i = 0; i < len; i++ ){
			fprintf(stdout, "Inserisci %d° numero: ", i+1);
			fscanf(stdin, "%d", &tmp);
			a[i]=tmp;	
		}
	}

	fprintf(stdout, "generateArray terminata correttamente\n");
}

int** generateMatrixRadix( int len, int cifre ){

	//Gli interi saranno inseriti in una matrice in cui ogni casella conterrà una cifra
	int** m = malloc( len*sizeof(int*) );
	char c;

	//Chidiamo se vogliamo la generazione randomica o meno
	fprintf(stdout, "Vuoi generare randomicamente i numeri (y/n) ? ");
	fscanf(stdin, "%c", &c);

	//Ad ogni iterazione verrà inserito un numero di 'cifre' cifre quindi ogni array sarà di lunghezza 'cifre'
	for(int i = 0; i<len; i++){
		m[i] = malloc( cifre*sizeof(int) );
				
		if( c == 'y' )
			generateArray(RANDOM, m[i], cifre, 9);
		else
			generateArray(NOTRANDOM, m[i], cifre);

		#ifdef DEBUG
			printArray(m[i], cifre);
		#endif
	}

	return m;
}

int findMax( int* a, int l ){

	int max = 0;

	for( int i = 0; i<l; i++ ){
		if( a[i] > max ){
			max = a[i];
		}
	}

	#ifdef DEBUG
		fprintf(stdout, "max: %d\n", max);
	#endif

	return max;
}

int findMin( int* a, int l ){

	int min = LIMITE;

	for( int i = 0; i<l; i++ ){
		if( a[i] < min ){
			min = a[i];
		}
	}

	#ifdef DEBUG
		fprintf(stdout, "min: %d\n", min);
	#endif

	return min;
}

int* countingSort( int* a, int lenA ){

	int max = findMax( a, lenA );
	int min = findMin( a, lenA );

	int lenC = max+1;
	int *c = calloc( lenC, sizeof(int) );

	#ifdef DEBUG
		printArray(c, lenC);
	#endif

	//STEP 1
	for( int i = 0; i<lenA; i++ ){
		c[a[i]]++;
	}

	#ifdef DEBUG
		printArray(c, lenC);
	#endif	

	//STEP 2
	for( int i = 1; i<lenC; i++){
		c[i] = c[i-1]+c[i];
	}

	#ifdef DEBUG
		printArray(c, lenC);
	#endif

	//STEP 3
	int* b = malloc( lenA*sizeof(int) );
		
	for( int i = lenA-1; i>=0; i-- ){
		//-1 perchè va nella c[a[i]]esima posizione, ma in C gli array partono da 0
		b[c[a[i]]-1] = a[i];
		c[a[i]]--;
	}

	#ifdef DEBUG
		printArray(b, lenA);
	#endif
	
	return b;
}

void buildArray( int* a, int heapsize){

	//Partiamo da heapsize/2 perchè tutti i valori con indici superiori sono foglie.
	for(int j = heapsize/2; j>0; j--){
		#ifdef DEBUG
			fprintf(stdout, "\nbuildArray: j = %d\n", j );
		#endif

		heapify(a, j, heapsize);
	}

}

void heapify( int* a, int i, int heapsize ){

	/*Nelle dispense gli array vanno da 1 ad n, in C NO. Quindi io mi calcolo in 
	builtArray l'indice come se gli array andassero da 1 ad e in questa funzione 
	compenso sottraendo 1 ogni volta che occore i. Ovviamente quando uso la ricosione
	passando maggiore come argomento dovrò incrementare di 1 siccome rientrando in
	questa funzione c'è la sottrazione per compensare. */

	int sn = i*2-1;
	int ds = (i*2)+1-1;
	#ifdef DEBUG
		fprintf(stdout, "a[%d]: %d - a[%d]: %d - a[%d]: %d\n", i-1, a[i-1], sn, a[sn], ds, a[ds]);
	#endif
		
	int maggiore = i-1;

	//Con i primi 2 if cerchiamo, se esiste con valore superiore al padre, il figlio con valore maggiore.
	if( sn < heapsize && a[sn] > a[maggiore] ){
		#ifdef DEBUG
			fprintf(stdout, "primo if: a[%d]: %d - a[%d] - %d\n", sn, a[sn], maggiore, a[maggiore]);
		#endif

		maggiore = sn;
	}
	if( ds < heapsize && a[ds] > a[maggiore] ){
		#ifdef DEBUG
			fprintf(stdout, "secondo if: a[%d]: %d - a[%d] - %d\n", ds, a[ds], maggiore, a[maggiore]);
		#endif

		maggiore = ds;
	}
	//Switch dei valori e richiamo ricorsivo di heapify per ricostruire la struttura di heap anche nel sottoalbero.
	if( maggiore != i-1){
		#ifdef DEBUG
			fprintf(stdout, "a[%d]: %d - a[%d]: %d\n",i-1, a[i-1], maggiore, a[maggiore] );
		#endif

		int tmp = a[i-1];
		a[i-1] = a[maggiore];
		a[maggiore] = tmp;

		fprintf(stdout, "\nStampiamo l'array poi chiamiamo ricorsivamente heapify:\n");
		printArray(a, heapsize);
		//fprintf(stdout, "\npremi INVIO per continuare...\n");
		//getchar();
		heapify(a, maggiore+1, heapsize);
	}
}

void heapsor(int* a, int heapsize){

	fprintf(stdout, "\n- - - - - - - COSTRUIAMO L'HEAP: - - - - - - - \n");

	buildArray(a, heapsize);
	fprintf(stdout, "\n - - - - - - - STAMPIAMO L'ALBERO: - - - - - - - - \n");
	printHeap(a,heapsize);

	fprintf(stdout, " - - - - - - - ORDINIAMO L'HEAP: - - - - - - - \n");
	//1 è la seconda posizione, ecco perchè sui lucidi c'è DOWNTO 2.
	for(int i = heapsize-1; i>=1; i--){
		#ifdef DEBUG
			fprintf(stdout, "i: %d -  heapsize: %d\n", i, heapsize);
		#endif

		int tmp = a[i];
		a[i] = a[0];
		a[0] = tmp;

		heapify(a, 1, --heapsize);
		
	}
}

int** ordinamentoRadix( int** m, int* s, int len, int cifre, int cifraInOrdinamento ){

	//Allochiamo lo spazio per l'array che poi verrà usato nel return
	int **b = malloc( len * sizeof(int*) );
	for( int i = 0; i < len; i++ ){
		b[i] = malloc( cifre * sizeof(int) );
	}

	//Il ciclo più esterno serve per scorrere gli indici si s[]. Prima cerchiamo 
	//il numero più piccolo a che numero corrisponde, e poi copiamo quel numero in
	//posizione b[i]. Finito il ciclo interno m = b siccome abbiamo modificato m
	//per evitare di effettuare dei confronti sbagliati quindi non possiamo più
	//usarlo nell'iterazione successiva, mentre b[] contiene i numeri corretti e
	//parzialmente ordinati. 
	//TODO: Sta cosa spreca un sacco di memoria, va modificata < - - - - - - - 
	for( int i = 0; i < len; i++ ){
		for( int j = 0; j < len; j++ ){
			if( m[j][cifraInOrdinamento] != s[i] )
				continue;
			else{
				copiaArray( b[i], m[j], cifre );
				m[j][cifraInOrdinamento] = -1;
				break;
			}
		}
	} 

	return b;
}

void copiaArray(int* b, int* m, int len){

	for( int i = 0; i < len; i++ ){
		b[i] = m[i];
	}

	#ifdef DEBUG
		printArray(m, len);
		printArray(b, len);
	#endif
}

int** radixSort( int** m, int len, int cifre ){

	int *tmp = calloc( len, sizeof(int) );
	int *step;

	for( int i = cifre-1; i >= 0; i-- ){
		for( int j = 0; j < len; j++ ){ 
			tmp[j] = m[j][i];
		}
		fprintf(stdout, "- - - - - - - - CIFRE DA ORDINARE E CIFRE ORDINATE - - - - - - - -\n\n");
		fprintf(stdout, "tmp[]:\n");
		printArray(tmp, len);
		

		step = countingSort( tmp, len );
		fprintf(stdout, "step[]:\n");
		printArray(step, len);
		fprintf(stdout, "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n");
		m = ordinamentoRadix( m, step, len, cifre, i);

		fprintf(stdout, "- - - - - - - - - - - - - STEP %d - - - - - - - - - - - - - - - - -\n\n", i+1);
		printMatrix(m, len, cifre);
		fprintf(stdout, "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n ");
		sleep(1);

	}

	return m;
}