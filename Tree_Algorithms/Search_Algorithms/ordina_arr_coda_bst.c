/*
 *
 *	@author Elia Renzoni
 *	@date 28/05/2023
 *	@brief ordinamento di un array, inserire i valori in una coda e in un albero bst, e cercare un valore, il quale successivamente dovra' essere eliminato solo se possibile in ordine FIFO
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_GEN 4

typedef struct coda {
	int valore;
	struct coda *succ;
} coda_t;

typedef struct albero {
	int chiave;
	struct albero *sx, *dx;
} albero_t;

void heapsort(int *, int);
void crea_max_heap(int *, int, int);
void crea_coda(coda_t **, coda_t **, int);
void crea_bst(albero_t **, int);
albero_t *cerca_in_bst(albero_t *, int);
coda_t *rimuovi_elem_coda(coda_t **, coda_t **);

int main(void) {

	albero_t *radice = NULL, *nodo_cercato = NULL;
	coda_t *ingresso = NULL, *uscita = NULL, *elem_rem = NULL;
	int contatore, valore, numero_elementi, *array, esito_lettura, acquisizione_errata, val_cerc;
	
	do {
		printf("Inserisci il numero degli elementi > \n");
		esito_lettura = scanf("%d", &numero_elementi);
		printf("Inserisci il valore da ricercare > \n");
		esito_lettura = scanf("%d", &val_cerc);
		acquisizione_errata = esito_lettura != 1 || numero_elementi < 1 || numero_elementi >= INT_MAX || val_cerc >= INT_MAX || val_cerc < 0;
		if (acquisizione_errata)
			printf("Errore !\n");
		while (getchar() != '\n');
	} while (acquisizione_errata);
	
	array = (int *)calloc(numero_elementi, sizeof(int));
	srand(time(NULL));
	for (contatore = 1; (contatore <= numero_elementi); contatore++) {
		valore = rand() % (numero_elementi * MAX_GEN);
		array[contatore] = valore;
	}
	heapsort(array, numero_elementi);
	for (contatore = 1; (contatore <= numero_elementi); contatore++) {
		crea_coda(&uscita, &ingresso, array[contatore]);
		crea_bst(&radice, array[contatore]);
	}
	nodo_cercato = cerca_in_bst(radice, val_cerc);
	if (nodo_cercato != NULL && nodo_cercato->chiave == uscita->valore) {
		printf("Valore Trovato !\n");
		elem_rem = rimuovi_elem_coda(&uscita, &ingresso);
		if (elem_rem != NULL)
			printf("Valore Eliminabile !\n");
		else
			printf("Valore non Eliminabile !\n");
	}
	else 
		printf("Valore non trovato !\n");
	
	free(uscita);	
	free(radice);

	return (0);
}

void heapsort(int *array, int numero_elementi) {
	
	int tmp, sx, dx;

	for (sx = numero_elementi / 2; (sx >= 1); sx--) 
		crea_max_heap(array, sx, numero_elementi);
	for (dx = numero_elementi; (dx > 1); dx--) {
		tmp = array[1];
		array[1] = array[dx];
		array[dx] = tmp;
		crea_max_heap(array, 1, dx - 1);
	}
}

void crea_max_heap(int *array, int sx, int dx) {
	
	int nuovo_valore, i, j;

	for (nuovo_valore = array[sx], i = sx, j = 2 * i; (j <= dx);) {
		if (j < dx && array[j + 1] > array[j])
			j++;
		if (nuovo_valore < array[j]) {
			array[i] = array[j];
			i = j;
			j = 2 * i;
		}
		else
			j = dx + 1;	
	}
	if (i != sx)
		array[i] = nuovo_valore;
}

void crea_coda(coda_t **uscita, coda_t **ingresso, int valore_ins) {
	
	coda_t *nuovo_elem = (coda_t *)malloc(sizeof(coda_t));
	nuovo_elem->valore = valore_ins;
	nuovo_elem->succ = NULL;
	if (*ingresso != NULL)
		(*ingresso)->succ = nuovo_elem;
	else
		*uscita = nuovo_elem;
	*ingresso = nuovo_elem;

}

void crea_bst(albero_t **radice, int valore_ins) {
	
	albero_t *nodo, *nuovo_nodo, *nodo_padre;

	for (nodo_padre = nodo = *radice; 
			(nodo != NULL); 
		nodo_padre = nodo, nodo = (valore_ins < nodo->chiave)? nodo->sx : nodo->dx);

	if (nodo == NULL) {
		nuovo_nodo = (albero_t *)malloc(sizeof(albero_t));
		nuovo_nodo->chiave = valore_ins;
		nuovo_nodo->sx = nuovo_nodo->dx = NULL;
		if (nodo == *radice) 
			*radice = nuovo_nodo;
		else
			if (valore_ins < nodo_padre->chiave)
				nodo_padre->sx = nuovo_nodo;
			else
				nodo_padre->dx = nuovo_nodo;
	}

}

albero_t *cerca_in_bst(albero_t *radice, int valore_cercare) {
	
	albero_t *nodo;

	for (nodo = radice; 
		(nodo != NULL && nodo->chiave != valore_cercare); 
	    nodo = (valore_cercare < nodo->chiave)? nodo->sx : nodo->dx);

	return (nodo);
}

coda_t *rimuovi_elem_coda(coda_t **uscita, coda_t **ingresso) {

	coda_t *elem_rem = *uscita;
	if (*uscita != NULL) {
		*uscita = elem_rem->succ;
		if (*uscita == NULL)
			*ingresso = NULL;
	}
	return (elem_rem);
}
