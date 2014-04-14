#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funzioniordinamento.h"

typedef struct {
	int num;
	struct list* next;
} list;



int main(int argc, char const *argv[]){
	/* code */
	return 0;
}


int* bucketSort(int vect[],int n){
	list* repetitions = (list*)calloc(n, sizeof(list*)); 
}

list* push(list* new,list* queue){
	/*
		Arrivo in fondo alla coda (dove il puntatore punta a NULL )
		e gli aggancio l'indirizzo del nuovo elemento.
	*/
	//puntatore che scala la coda arrivando alla fine
	list* next;
	//se mi accorgo che l'inizo della coda punta subito a NULL
	//faccio a meno di cominciare la scalata
	if(queue == NULL){
		queue = new;
		return new;
	}else{
		//altrimenti scalo la lista
		next = queue;
		while(next->next != NULL){
			next = next->next;
		}
	}
}