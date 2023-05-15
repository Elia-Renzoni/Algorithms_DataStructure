/*
 *	@author Elia Renzoni
 *	@date 15/05/2023
 *	@brief dato un valore target K, determinare se la somma dei nodi che si incontrano in un albero e' uguale a k, in caso affermativo restituire una lista con quei nodi
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 20

typedef struct albero {
	int chiave;
	struct albero *figlio_sx, *figlio_dx;
} albero_t;

typedef struct lpath {
	int chiave_n;
	struct lpath *successivo;
} lpath_t;

void crea_albero_bst(albero_t **, int);
int  cerca_somma_target(albero_t *, int);
void crea_lista(lpath_t **, int);
void visita_lista(lpath_t *);

int main(void) {

	albero_t *radice = NULL;
	int contatore, numero_elementi, valore, chiave_ricerca, esito_ricerca;
	int esito_lettura, acquisizione_errata;

	do {
		printf("Inserisci il numero di elementi dell'albero e la chiave di ricerca > \n");
		esito_lettura = scanf("%d", &numero_elementi);
		esito_lettura = scanf("%d", &chiave_ricerca);
		acquisizione_errata = esito_lettura != 1 || numero_elementi < 1;
		if (acquisizione_errata)
			printf("Errore ! \n");
		while (getchar() != '\n');
	} while (acquisizione_errata);

	srand(time(NULL));
	for (contatore = 0; (contatore < numero_elementi); contatore++) {
		valore = rand() % (numero_elementi * MAX_N);
		crea_albero_bst(&radice, valore);
	}

	esito_ricerca = cerca_somma_target(radice, chiave_ricerca);
	if (esito_ricerca) {
		printf("Valore Trovato!\n");
	}
	else {
		printf("Valore non trovato !\n");
	}

	return (0);

}

/*
 *	@brief creazione albero binario di ricerca
 * */
void crea_albero_bst(albero_t **radice, int valore_inserire) {

	albero_t *nodo, *nuovo_nodo, *nodo_padre;

	for (nodo_padre = nodo = *radice; 
			(nodo != NULL && nodo->chiave != valore_inserire);
		       	nodo_padre = nodo, nodo = (valore_inserire < nodo->chiave)? nodo->figlio_sx : nodo->figlio_dx);

	if (nodo == NULL) {
		nuovo_nodo = (albero_t *)malloc(sizeof(albero_t));
		nuovo_nodo->chiave = valore_inserire;
		nuovo_nodo->figlio_sx = nuovo_nodo->figlio_dx = NULL;
		if (nodo == *radice) 
			*radice = nuovo_nodo;
		else
			if (valore_inserire < nodo_padre->chiave)
				nodo_padre->figlio_sx = nuovo_nodo;
			else
				nodo_padre->figlio_dx = nuovo_nodo;
	}

}

/*
 *	@brief algoritmo di ricerca su un albero bin di ricerca
 * */
int cerca_somma_target(albero_t *radice, int target) {

	int esito_ricerca, somma = 0;
	lpath_t *testa_lista = NULL;
	albero_t *nodo;

	for (nodo = radice; (nodo != NULL && somma != target); nodo = (target < nodo->chiave)? nodo->figlio_sx : nodo->figlio_dx) {
		somma += nodo->chiave;
		crea_lista(&testa_lista, nodo->chiave);
	}

	if (somma == target) {
		visita_lista(testa_lista);
		esito_ricerca = 1;
	}
	else {
		esito_ricerca = 0;
		free(testa_lista);
	}
	
	return (esito_ricerca);

}

/*
 *	@brief algoritmo per creare la creazione di una lista sing. concat
 * */
void crea_lista(lpath_t **testa, int valore_inserire) {

	lpath_t *elemento, *precedente, *nuovo_elemento;

	for (precedente = elemento = *testa; (elemento != NULL); precedente = elemento, elemento = elemento->successivo);

	if (elemento == NULL) {
		nuovo_elemento = (lpath_t *)malloc(sizeof(lpath_t));
		nuovo_elemento->chiave_n = valore_inserire;
		nuovo_elemento->successivo = NULL;
		if (elemento == *testa)
			*testa = nuovo_elemento;
		else
			precedente->successivo = nuovo_elemento;
	}

}

/*
 *	@brief algoritmo di visita di una lista 
 * */
void visita_lista(lpath_t *testa) {

	lpath_t *elemento;

	for (elemento = testa; (elemento != NULL); elemento = elemento->successivo)
		printf("%d\n", elemento->chiave_n);

}

