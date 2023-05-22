/*
 *	@author Elia Renzoni
 *	@date 22/05/2023
 *	@brief crea un array, inserisci in coda i valori, inserisci in un albero BST i valori e restituisci la dimensionne dell'array, 
 *	della coda e restituisci il grado massimo, il numero massimo e la profondita di un albero
 * */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct tree {
	int chiave;
	struct tree *figlio_sx, *figlio_dx;
} tree_t;

typedef struct coda {
	int valore;
	struct coda *successivo;
} coda_t;

int *crea_array(int);
void inserimento_array(int *, int, int);
void inserimento_coda(coda_t **, coda_t **, int);
void inserimento_albero_bst(tree_t **, int);
int calcola_dimensione_coda(coda_t *);
int calcola_grado_massimo_albero(tree_t *);
void calcola_profondita_albero(tree_t *, int *);

int main(void) {

	coda_t *uscita = NULL, *ingresso = NULL;
	tree_t *radice = NULL;
	int *arr_valori = NULL, numero_elementi, valore_elem, contatore, profondita_f = 1, profondita_s = 1;
	int esito_lettura, acquisizione_errata;

	do {
		printf("Inserisci il numero degli elementi > \n");
		esito_lettura = scanf("%d", &numero_elementi);
		acquisizione_errata = esito_lettura != 1 || numero_elementi < 1 || numero_elementi > INT_MAX;
		if (acquisizione_errata)
			printf("Errore ! \n");
		while (getchar() != '\n');
	} while (acquisizione_errata);

	arr_valori = crea_array(numero_elementi);
	srand(time(NULL));
	for (contatore = 0; (contatore < numero_elementi); contatore++) {
		valore_elem = rand() % (numero_elementi * numero_elementi);
		inserimento_array(arr_valori, contatore, valore_elem);
		inserimento_coda(&uscita, &ingresso, valore_elem);
		inserimento_albero_bst(&radice, valore_elem);
	}
	
	printf("Dimensione Array : %d \n", numero_elementi);
	printf("Dimensione Coda : %d \n", calcola_dimensione_coda(uscita));
	printf("Grado Albero BST : %d \n", calcola_grado_massimo_albero(radice));

	calcola_profondita_albero(radice->figlio_sx, &profondita_f);
	calcola_profondita_albero(radice->figlio_dx, &profondita_s);

	if (profondita_f > profondita_s)
		printf("Profondita massima : %d \n", profondita_f);
	else
		printf("Profondita massima : %d \n", profondita_s);

	free(uscita);
	free(radice);
	free(arr_valori);
	
	return (0);
}


int *crea_array(int numero_elementi) {

	int *array = (int *)calloc(numero_elementi, sizeof(int));

	return (array);
}

void inserimento_array(int *array, int contatore, int valore) {
	
	array[contatore] = valore;
}

void inserimento_coda(coda_t **uscita, coda_t **ingresso, int valore) {

	coda_t *nuovo_elemento = (coda_t *)malloc(sizeof(coda_t));
	nuovo_elemento->valore = valore;
	if (*ingresso != NULL) 
		(*ingresso)->successivo = nuovo_elemento; 
	else 
		*uscita = nuovo_elemento;

	*ingresso = nuovo_elemento;

}

void inserimento_albero_bst(tree_t **radice, int valore_ins) {

	tree_t *nuovo_nodo, *nodo_g, *nodo_padre;

	for (nodo_padre = nodo_g = *radice; 
			(nodo_g != NULL); 
	     nodo_padre = nodo_g, nodo_g = (valore_ins < nodo_g->chiave)? nodo_g->figlio_sx : nodo_g->figlio_dx);
	
	if (nodo_g == NULL) {

		nuovo_nodo = (tree_t *)malloc(sizeof(tree_t));
		nuovo_nodo->chiave = valore_ins;
		nuovo_nodo->figlio_sx = NULL, nuovo_nodo->figlio_dx = NULL;
		if (nodo_g == *radice) 
			*radice = nuovo_nodo;
		else 
			if (valore_ins < nodo_padre->chiave)
				nodo_padre->figlio_sx = nuovo_nodo;
			else
				nodo_padre->figlio_dx = nuovo_nodo;
		
	}

}

int calcola_dimensione_coda(coda_t *uscita) {

	coda_t *oggetto;
	int dim = 0;

	for (oggetto = uscita; (oggetto != NULL); oggetto = oggetto->successivo)
		dim += 1;

	return (dim);

}

int calcola_grado_massimo_albero(tree_t *radice) {

	int grado_max = 1;
	tree_t *nodo;

	for (nodo = radice; (nodo != NULL); nodo = nodo->figlio_sx)
		if (nodo->figlio_sx != NULL && nodo->figlio_dx != NULL)
			grado_max = 2;
	for (nodo = radice; (nodo != NULL); nodo = nodo->figlio_dx)
		if (nodo->figlio_dx != NULL && nodo->figlio_sx != NULL)
			grado_max = 2;

	return (grado_max);

}

void calcola_profondita_albero(tree_t *radice, int *prof) {

	if (radice != NULL) {
		calcola_profondita_albero(radice->figlio_sx, prof);
		(*prof)++;
		calcola_profondita_albero(radice->figlio_dx, prof);
	}

}
