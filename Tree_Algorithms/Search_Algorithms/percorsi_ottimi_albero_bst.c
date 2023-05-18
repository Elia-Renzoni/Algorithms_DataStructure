/*
 *
 *	@author Elia Renzoni
 *	@date 17/05/2023
 *	@brief ricerca i percorsi ottimi in un albero di ricerca binario. Vi sono percorsi ottimi se dato un nodo n-esimo il suo successore e' maggiore
 *	viene fornito un array contente gli indici e un array contenente i valori.
 *
 * */


#include <stdio.h>
#include <stdlib.h>

#define MAX_ITER 2

typedef struct {
	int indice, chiave;
} ins_binario_t;

typedef struct albero {
	ins_binario_t valore;
	struct albero *figlio_sx, *figlio_dx;
} albero_t;

int *creazione_array(int, int);
void creazione_albero_bst(albero_t **, int, int);
void visita_ord_simmetrico(albero_t *);
int  ricerca_path_albero_bst(albero_t *);

int main(void) {

	int *arr_indici = NULL, *arr_chiavi = NULL, numero_elementi, lunghezza_percorso;
	albero_t *radice_albero = NULL;
	int esito_lettura, acquisizione_errata, contatore;

	do {
		printf("Inserisci il numero degli elementi degli array > \n");
		esito_lettura = scanf("%d", &numero_elementi);
		acquisizione_errata = esito_lettura != 1 || numero_elementi < 1;
		if (acquisizione_errata)
			printf("Errore ! \n");
		while (getchar() != '\n');
	} while (acquisizione_errata);

	for (contatore = 0; (contatore < MAX_ITER); contatore++) 
		if (contatore == 0) 
			arr_indici = creazione_array(numero_elementi, contatore);
		else
			arr_chiavi = creazione_array(numero_elementi, contatore);

	for (contatore  = 0; (contatore < numero_elementi); contatore++) 	
		creazione_albero_bst(&radice_albero, arr_indici[contatore], arr_chiavi[contatore]);
	
	printf("Albero > \n");
	visita_ord_simmetrico(radice_albero);
	lunghezza_percorso = ricerca_path_albero_bst(radice_albero);
	if (lunghezza_percorso > 0) 
		printf("Percorso %d \n", lunghezza_percorso);
	else
		printf("Percorso non trovato ! \n");

	return (0);

}


/*
 *	@brief algoritmo per la creazione e il riempimento dei due array
 * */
int *creazione_array(int numero_elementi, int contatore) {

	int *indici = NULL, *chiavi = NULL;
	int val_indici = 0, val_chiavi = 0, i;

	srand(1);
	if (contatore == 0) {
		indici = (int *)calloc(numero_elementi, sizeof(int));
		for (i = 0; (i < numero_elementi); i++) {
			val_indici++;
			indici[i] = val_indici;
		}
	}
	else if (contatore == 1) {
		chiavi = (int *)calloc(numero_elementi, sizeof(int));
		for (i = 0; (i < numero_elementi); i++) {
			val_chiavi = rand() % (numero_elementi * numero_elementi);
			chiavi[i] = val_chiavi;
		}
	}

	return ((contatore == 0)? indici : chiavi);
}

/*
 *	@brief algoritmo per la creazione di un albero binairo di ricerca
 * */
void creazione_albero_bst(albero_t **radice, int ind_nodo, int val_nodo) {

	albero_t *nodo, *nuovo_nodo, *nodo_padre;
	
	for (nodo_padre = nodo = *radice; 
			(nodo != NULL); 
	    nodo_padre = nodo, nodo = (val_nodo < nodo->valore.chiave)? nodo->figlio_sx : nodo->figlio_dx);

	if (nodo == NULL) {
		nuovo_nodo = (albero_t *)malloc(sizeof(albero_t));
		nuovo_nodo->valore.indice = ind_nodo;
		nuovo_nodo->valore.chiave = val_nodo;
		nuovo_nodo->figlio_sx = nuovo_nodo->figlio_dx = NULL;
		if (nodo == *radice)
			*radice = nuovo_nodo;
		else 
			if (val_nodo < nodo_padre->valore.chiave)
				nodo_padre->figlio_sx = nuovo_nodo;
			else
				nodo_padre->figlio_dx = nuovo_nodo;
	}

}

/*
 *	@brief visita albero ordine simmetrico
 * */
void visita_ord_simmetrico(albero_t *radice) {

	if (radice != NULL) {
		visita_ord_simmetrico(radice->figlio_sx);
		printf("%d - %d\n", radice->valore.indice, radice->valore.chiave);
		visita_ord_simmetrico(radice->figlio_dx);
	}

}

/*
 *	@brief algoritmo di ricerca del percorso ottimo.
 * */
int ricerca_path_albero_bst(albero_t *radice) {

	int numero_path = 0;
	albero_t *nodo;

	for (nodo = radice; (nodo != NULL); nodo = nodo->figlio_sx)
		++numero_path;

	return (numero_path);

}

