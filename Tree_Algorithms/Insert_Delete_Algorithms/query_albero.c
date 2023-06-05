/*
 *
 *	@author Elia Renzoni
 *	@date 05/06/2023
 *	@brief dato un albero bst e un array query, andare a rimuovere gli elementi i-esimi dall'albero e restituire l'altezza dell'albero in
 *	seguito ad ogni rimozione.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct bst {
	int chiave;
	struct bst *figlio_sx, *figlio_dx;
} bst_t;

int *crea_query(int *, int);
int inserisci_in_albero(bst_t **, int);
int rimuovi_da_albero(bst_t **, int);
int calcola_altezza_albero(bst_t *);
void visita_ordine_simmetrico(bst_t *, int *);

int main(void) {

	bst_t *radice = NULL;
	int *query = NULL;
	int numero_elementi_q, numero_elementi_a, valore, esito_lettura, acq_err, contatore;

	do {
		printf("Inserisci il numero degli elementi dell'albero > \n");
		esito_lettura = scanf("%d", &numero_elementi_a);
		acq_err = esito_lettura != 1 || numero_elementi_a < 1;
		if (acq_err)
			printf("Errore !\n");
		while (getchar() != '\n');
	} while (acq_err);

	srand(time(NULL));
	for (contatore = 0; (contatore < numero_elementi_a); contatore++) {
		valore = rand() % (numero_elementi_a * numero_elementi_a);
		inserisci_in_albero(&radice, valore);
	}
	query = crea_query(&numero_elementi_q, numero_elementi_a);
	for (contatore = 0; (contatore < numero_elementi_q); contatore++) {
		rimuovi_da_albero(&radice, query[contatore]);
		printf("Altezza > %d \n", calcola_altezza_albero(radice));
	}

	return (0);

}

int *crea_query(int *numero_elementi, int elementi_albero) {

	int *query;
        int valore, contatore, esito_lettura, acq_err;

	do {
		printf("Inserisci il numero degli elementi della query > \n");
		esito_lettura = scanf("%d", numero_elementi);
		acq_err = esito_lettura != 1 || *numero_elementi >= elementi_albero;
		if (acq_err)
			printf("Errore !\n");
		while (getchar() != '\n');
	} while (acq_err);

	query = (int *)calloc(*numero_elementi, sizeof(int));
	srand(time(NULL));
	for (contatore = 0; (contatore < *numero_elementi); contatore++) {
		valore = rand() % *numero_elementi;
		query[contatore] = valore;
	}

	return (query);

}

int inserisci_in_albero(bst_t **radice, int valore_ins) {
	
	bst_t *nodo, *nuovo_nodo, *nodo_padre;
	int esito_inserimento;

	for (nodo_padre = nodo = *radice; 
			(nodo != NULL && nodo->chiave != valore_ins); 
		nodo_padre = nodo, nodo = (valore_ins < nodo->chiave)? nodo->figlio_sx : nodo->figlio_dx);

	if (nodo != NULL) 
		esito_inserimento = 0;
	else {
		esito_inserimento = 1;
		nuovo_nodo = (bst_t *)malloc(sizeof(bst_t));
		nuovo_nodo->chiave = valore_ins;
		nuovo_nodo->figlio_sx = nuovo_nodo->figlio_dx = NULL;
		if (nodo == *radice) 
			*radice = nuovo_nodo;
		else 
			if (valore_ins < nodo_padre->chiave)
				nodo_padre->figlio_sx = nuovo_nodo;
			else
				nodo_padre->figlio_dx = nuovo_nodo;
	}

	return (esito_inserimento);

}	

int rimuovi_da_albero(bst_t **radice, int valore_rem) {

	bst_t *nodo, *nodo_padre, *nodo_sost;
	int esito_rimozione;

	for (nodo = nodo_padre = *radice; 
			(nodo != NULL && nodo->chiave != valore_rem); 
		nodo_padre = nodo, nodo = (valore_rem < nodo->chiave)? nodo->figlio_sx : nodo->figlio_dx);

	if (nodo == NULL)
		esito_rimozione = 0;
	else {
		esito_rimozione = 1;
		if (nodo->figlio_sx == NULL) 
			if (nodo == *radice)
				*radice = nodo->figlio_dx;
			else
				if (valore_rem < nodo_padre->chiave)
					nodo_padre->figlio_sx = nodo->figlio_dx;
				else
					nodo_padre->figlio_dx = nodo->figlio_dx;
		else
			if (nodo->figlio_dx == NULL)
				if (nodo == *radice)
					*radice = nodo->figlio_sx;
				else
					if (valore_rem < nodo->chiave)
						nodo_padre->figlio_sx = nodo->figlio_sx;
					else
						nodo_padre->figlio_dx = nodo->figlio_sx;
			else {
				nodo_sost = nodo;
				for (nodo_padre = nodo_sost, nodo = nodo_sost->figlio_sx; 
						(nodo != NULL); 
				     nodo_padre = nodo, nodo = nodo->figlio_dx);

				if (nodo_padre == nodo_sost)
					nodo_padre->figlio_sx = nodo->figlio_sx;
				else
					nodo_padre->figlio_dx = nodo->figlio_sx;
			}
		free(nodo);
	}

	return (esito_rimozione);

}

int calcola_altezza_albero(bst_t *radice) {

	int altezza, numero_nodi;

	visita_ordine_simmetrico(radice, &numero_nodi);
	altezza = log(numero_nodi);
	
	return (altezza);
	
}

void visita_ordine_simmetrico(bst_t *radice, int *numero_nodi) {
	
	if (radice != NULL) {
		visita_ordine_simmetrico(radice->figlio_sx, numero_nodi);
		*numero_nodi += 1;
		visita_ordine_simmetrico(radice->figlio_dx, numero_nodi);
	}

}
