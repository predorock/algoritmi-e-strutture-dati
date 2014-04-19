#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <stdarg.h>
#include <unistd.h>
#include "funzioniordinamento.h"

//Si commenta sempre da sola
void printArray( void* a, int l, char* tipo ){


		if( strcmp( tipo, "int" ) == 0 ){
			int *tmp;
			tmp = a;

			for( int i = 0; i < l; i++ )
				fprintf(stdout, "%d ", tmp[i]);
			putchar('\n');
		}

		else if( strcmp( tipo, "double" ) == 0 ){
			double *tmp;
			tmp = a;

			for( int i = 0; i < l; i++ )
				fprintf(stdout, "%f ", tmp[i]);
			putchar('\n');
		}

		else
			fprintf(stdout, "Errore di tipo: %s non esiste\n", tipo);
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

void* generateArray( int num, int tipo, int len, ... ){

	//VARARGS
	va_list arguments;			//Variabile di tipo va_list
	va_start(arguments, len);	//Facciamo iniziare la lista all'argomento len

	char c;
	int range;

	//Se i numeri abbiamo deciso di inserirli randomicamente avremo un 4°
	//argomento in ingresso alla funzione che mi indicherà il range entro
	//il quale devo generare i numeri.
		if( tipo == INT ){ 
			int* a = malloc( len * sizeof(int) );

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

			printArray(a, len, "int");
			fprintf(stdout, "generateArray per INT terminata correttamente\n");

			return a;
		}

		else if( tipo == DOUBLE ){
			double *a = malloc( len*sizeof(double) );
			if( num == RANDOM ){
				c = 'y';			
				range = va_arg(arguments, int);		//Recuperiamo il valore del successivo argomento.
					
				#ifdef DEBUG
					fprintf(stdout, "range: %d", range);
				#endif		
			}

			//Se vogliamo generare i numeri randomicamente
			if( c == 'y'){
				for( int i = 0; i < len; i++ ){
					a[i]=rand()%range;
					printf("GeneateArray: i = %d, a[i] = %f\n", i, a[i]);
				}
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

			//#ifdef DEBUG
				printArray(a, len, "double");
				fprintf(stdout, "generateArray per DOUBLE terminata correttamente\n");
			//#endif

			return a;
		}

		else{
			fprintf(stdout, "Errore di tipo: %d non esiste o non ancora implementato\n", tipo);
			return NULL;
		}
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
			m[i] = generateArray(RANDOM, INT, cifre, 9);
		else
			m[i] = generateArray(NOTRANDOM, INT, cifre);

		#ifdef DEBUG
			printArray(m[i], cifre, "int");
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
		printArray(c, lenC, "int");
	#endif

	//STEP 1
	for( int i = 0; i<lenA; i++ ){
		c[a[i]]++;
	}

	#ifdef DEBUG
		printArray(c, lenC, "int");
	#endif	

	//STEP 2
	for( int i = 1; i<lenC; i++){
		c[i] = c[i-1]+c[i];
	}

	#ifdef DEBUG
		printArray(c, lenC, "int");
	#endif

	//STEP 3
	int* b = malloc( lenA*sizeof(int) );
		
	for( int i = lenA-1; i>=0; i-- ){
		//-1 perchè va nella c[a[i]]esima posizione, ma in C gli array partono da 0
		b[c[a[i]]-1] = a[i];
		c[a[i]]--;
	}

	#ifdef DEBUG
		printArray(b, lenA, "int");
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
		printArray(a, heapsize, "int");
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
		printArray(m, len, "int");
		printArray(b, len, "int");
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
		printArray(tmp, len, "int");
		

		step = countingSort( tmp, len );
		fprintf(stdout, "step[]:\n");
		printArray(step, len, "int");
		fprintf(stdout, "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n");
		m = ordinamentoRadix( m, step, len, cifre, i);

		fprintf(stdout, "- - - - - - - - - - - - - STEP %d - - - - - - - - - - - - - - - - -\n\n", i+1);
		printMatrix(m, len, cifre);
		fprintf(stdout, "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n ");
		sleep(1);

	}

	return m;
}

struct bucketList* createNode( double v ){

	struct bucketList *p;
	p = malloc( 1 * sizeof(struct bucketList) );

	p->val = v;
	p->next = NULL;
	
	printf("valore: %f\n", p->val);


	return p;
}

void addNode( struct bucketList *first, struct bucketList *p, int indice, int len ){

	printf("indice: %d\n", indice);

	struct bucketList *current = first[indice].next;
	struct bucketList *prev = &first[indice];
	
	#ifdef DEBUG
		printf("valore: %f\n", p->val);
		printf("current: %d, prev: %d NULL: %d\n", current, prev, NULL);
	#endif

	for( /*vuota*/; current != NULL; current = current->next, prev = prev->next ){
		if( current->val > p->val ){
			p->next = current;
			prev->next = p;

			printBucketList(first, len);

			return;
		}
	}
		
	prev->next = p;

	printBucketList(first, len);

	return;
}

void riempiListaBucket( struct bucketList *first, double limiteInf, double limiteSup, double *a, int len){

	//Se sto riempiendo la prima posizione di first step varrà 1 e cosi via.
	for(int i = 0; i<len; i++){
		printf("a[%d] = %f, limiteInf = %f, limiteSup = %f\n", i, a[i], limiteInf, limiteSup);
		if( (a[i] >= limiteInf) && (a[i] < limiteSup) ){
			printf("aggiungo nodo a[i] = %f, limiteSup: %f\n", a[i], limiteSup);
			printf("condizioni booleane: %d - %f - %d\n", (a[i] >= limiteInf), (limiteSup - a[i]), (0.30 < 0.3) );
			//Step torna a servirmi come indice di un array, quindi con valori che 
			//vanno da 0 a n-1, quindi sottraiamo 1.
			struct bucketList *tmp = createNode( a[i] );
			addNode( first, tmp, (limiteInf*len), len );
		}
	}

}

void printBucketList( struct bucketList *first, int len ){

	struct bucketList *p;

	for( int i = 0; i<len; i++ ){
		fprintf(stdout, "Lista in posizione %d: ", i);
		for( p = &first[i]; p->next != NULL; p = p->next ){
			fprintf(stdout, "%f ", p->next->val );
		}
		putchar('\n');
	}
}

double* riempiVettoreRisultato( struct bucketList *first, int len ){

	//Creiamo il vettore in cui mettiamo i numeri ordinati
	double *b;
	b = malloc( len*sizeof(double) );

	//Il ciclo esterno serve per scorrere i first in verticale.
	for( int i = 0, j = 0; i<len; i++ ){
		//Cerchiamo se ci sono elementi nelle varie liste e man mano che li incontriamo
		//li mettiamo nel vettore risultante.
		for( struct bucketList *current = first[i].next; current != NULL; current = current->next ){
			b[j++] = current->val;
		}
	}

	return b;
}


double* bucketSort( double* a, int len ){
	//La bucketList è un array di puntatori, ognuno che punta ad una lista contenenti
	//i numeri da un tot range ad un altro tot range.
	struct bucketList *first;
	first = calloc( len, sizeof(struct bucketList) );

	double *b;

	for( int i = 0; i<len; i++){
		first[i].next = NULL;
	}

	printBucketList(first, len);

	//Se len è 10 nella lista contenuta nella prima posizione dell'array andranno
	//i numeri da 0,0 < val <= 0,1, nella seconda posizione da 0,1 < val <= 0,2
	//e così via.
	double step = (1.0 / len);

	for( int i = 0; i < len; i++ ){
		//Siccome i sarà un fattore moltiplicativo mi serve che vada da 1 ad n e non
		//da 0 a n-1
		printf("\ni = %d, step = %f, %f %f\n", i, step, (step*i), ((step*i)+step) );
		riempiListaBucket( first, (step*i), ((step*i)+step), a, len );	
	}
	
	printBucketList( first, len );

	b = riempiVettoreRisultato( first, len );

	printArray(b, len, "double");

	return NULL;
}

int floatsEqual(float f1, float f2){
    return fabs(f1 - f2) < EPSILON; // or fabsf
}