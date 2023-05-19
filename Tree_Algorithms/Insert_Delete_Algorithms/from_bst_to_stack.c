/*
 *	@author ELia Renzoni
 *	@date 19/05/2023
 *	@brief creazione di un albero BST e ordinamento di un array usando uno stack
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct stack {
	int chiave;
	struct stack *successivo;
} stack_t;

typedef struct bst {
	int key;
	struct bst *figlio_sx, *figlio_dx;
} bst_t;

void creazione_albero_bst(bst_t **, int);
void visita_ordine_simmetrico(bst_t *, stack_t **);
void creazione_stack(stack_t **, int);
void ordina_array(stack_t *, int *);

int main(void) {

	int *arr_numeri = NULL, numero_elementi, valore;
	bst_t *radice_albero = NULL;
	stack_t *cima_stack = NULL;
	int esito_lettura, acquisizione_errata, contatore;

	do {
		printf("Inserisci il numero di elementi da generare > \n");
		esito_lettura = scanf("%d", &numero_elementi);
		acquisizione_errata = esito_lettura != 1 || numero_elementi < 1;
		if (acquisizione_errata)
			printf("Errore !\n");
		while (getchar() != '\n');
	} while (acquisizione_errata);
	
	arr_numeri = (int *)calloc(numero_elementi, sizeof(int));
	srand(time(NULL));
	for (contatore = 0; (contatore < numero_elementi); contatore++) {
		valore = rand() % (numero_elementi * numero_elementi);
		creazione_albero_bst(&radice_albero, valore);
		arr_numeri[contatore] = valore;
	}

	printf("Array non ordinato > \n");
	for (contatore = 0; (contatore < numero_elementi); contatore++) 
		printf("%d\n", arr_numeri[contatore]);
	visita_ordine_simmetrico(radice_albero, &cima_stack);
	ordina_array(cima_stack, arr_numeri);
	
	printf("Array Ordinato > \n");
	for (contatore  = 0; (contatore < numero_elementi); contatore++)
		printf("%d\n", arr_numeri[contatore]);

	free(radice_albero);
	free(arr_numeri);
	free(cima_stack);

	return (0);


}

/*
 *	@brief algoritmo per la creazione di un albero binario di ricerca
 * */
void creazione_albero_bst(bst_t **radice, int chiave) {

	bst_t *nodo, *nuovo_nodo, *nodo_padre;

	for (nodo_padre = nodo = *radice; 
			(nodo != NULL); 
		nodo_padre = nodo, nodo = (chiave < nodo->key)? nodo->figlio_sx : nodo->figlio_dx);

	if (nodo == NULL) {
		nuovo_nodo = (bst_t *)malloc(sizeof(bst_t));
		nuovo_nodo->key = chiave;
		nuovo_nodo->figlio_sx = nuovo_nodo->figlio_dx = NULL;
		if (nodo == *radice)
			*radice = nuovo_nodo;
		else 
			if (chiave < nodo_padre->key)
				nodo_padre->figlio_sx = nuovo_nodo;
			else
				nodo_padre->figlio_dx = nuovo_nodo;
	}

}

/*
 *	@brief algoritmo di visita in ordine simm.
 * */
void visita_ordine_simmetrico(bst_t *radice, stack_t **cima) {

	if (radice != NULL) {
		visita_ordine_simmetrico(radice->figlio_sx, cima);
		creazione_stack(cima, radice->key);
		visita_ordine_simmetrico(radice->figlio_dx, cima);
	}

}

/*
 *	@brief algoritmo per la creazione di una pila
 * */
void creazione_stack(stack_t **cima, int valore) {

	stack_t *nuovo_elem = (stack_t *)malloc(sizeof(stack_t));
	nuovo_elem->chiave = valore;
	nuovo_elem->successivo = *cima;
	*cima = nuovo_elem;

}

/*
 *	@brief algorimo per l'ordinamento di un array tramite stack
 * */
void ordina_array(stack_t *cima, int *arr_numeri) {

	stack_t *nodo;
	int contatore;

	for (nodo = cima, contatore = 0; (nodo != NULL); contatore++, nodo = nodo->successivo)
		arr_numeri[contatore] = nodo->chiave;

}
