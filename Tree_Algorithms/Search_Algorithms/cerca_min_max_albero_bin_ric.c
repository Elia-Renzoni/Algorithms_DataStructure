/*
 *
 *	@author Elia Renzoni
 *	@date   04/05/2023
 *	@brief  Leggere da un file e memorizzare il suo contenuto in un albero binario di ricerca, poi cercare il minimo e il massimo valore
 *
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct tree {
	int    numero;
	struct tree *figlio_sx, *figlio_dx;
} tree_t;

void creazione_albero_bin_ric(tree_t **, int);
int  cerca_massimo_albero_bin_ric(tree_t *);
int  cerca_minimo_albero_bin_ric(tree_t *);

int main(void) {

	tree_t *radice = NULL;
	int     contatore, numero_valori, chiavi;
	int     esito_lettura, fsc = 0;
	FILE   *database;

	database = fopen("database.txt", "w");
	printf("Inserire il numero di chiavi > \n");
	esito_lettura = scanf("%d", &numero_valori);

	if (esito_lettura != 1)
		printf("Errore !");

	srand(time(NULL));
	for (contatore = 0, chiavi = rand() % numero_valori; (contatore < numero_valori); contatore++, chiavi = rand() % numero_valori)
		fprintf(database, "%d\n", chiavi);
	fclose(database);

	database = fopen("database.txt", "r");
	for (contatore = 0; (contatore < numero_valori); contatore++) {
		fsc = fscanf(database, "%d", &chiavi);
		creazione_albero_bin_ric(&radice, chiavi);
	}
	if (fsc < 1)
		printf("Errore !\n");
	fclose(database);

	printf("Valore Massimo > %d \n", cerca_massimo_albero_bin_ric(radice));
	printf("Valore Minimo > %d \n", cerca_minimo_albero_bin_ric(radice));

	return (0);

}

/*
 *
 *	@brief Algoritmo per creare un albero binario di ricerca
 *
 * */
void creazione_albero_bin_ric(tree_t **radice, int chiave) {

	tree_t *nodo_n, *nuovo_nodo, *nodo_padre;

	for (nodo_padre = nodo_n = *radice; 
			((nodo_n != NULL) && (nodo_n->numero != chiave)); 
	    nodo_padre = nodo_n, nodo_n = (chiave < nodo_n->numero)? nodo_n->figlio_sx : nodo_n->figlio_dx);

	if (nodo_n == NULL) {
		nuovo_nodo = (tree_t *)malloc(sizeof(tree_t));
		nuovo_nodo->numero = chiave;
		nuovo_nodo->figlio_sx = nuovo_nodo->figlio_dx = NULL;

		if (nodo_n == *radice)
			*radice = nuovo_nodo;
		else 
			if (chiave < nodo_padre->numero)
				nodo_padre->figlio_sx = nuovo_nodo;
			else
				nodo_padre->figlio_dx = nuovo_nodo;
	}


}

/*
 *
 *	@brief Cerca il massimo valore di un  albero *
 * */
int cerca_massimo_albero_bin_ric(tree_t *radice) {

	int     valore_max = 0;
	tree_t *nodo;

	for (nodo = radice; (nodo != NULL); nodo = nodo->figlio_dx)
		valore_max = nodo->numero;

	return (valore_max);

}

/*
 *
 *	@brief Cerca il minimo valore di un albero
 *
 * */
int cerca_minimo_albero_bin_ric(tree_t *radice) {

	tree_t *nodo;
	int     valore_minimo = 0;

	for (nodo = radice; (nodo != NULL); nodo = nodo->figlio_sx)
		valore_minimo = nodo->numero;

	
	return (valore_minimo);


}
