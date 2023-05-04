/*
 *
 *	@author Elia Renzoni
 *	@date 04/05/2023
 *	@brief Somma dei nodi che hanno valore compreso tra due interi
 *
 *
 * */

#include <stdio.h>
#include <stdlib.h>


typedef struct albero {
	int          chiave;
	struct albero *figlio_sx, *figlio_dx;
} albero_t;

void creazione_bst(albero_t **, int);
int  somma_vincolata(albero_t *, int, int);

int main(void) {

	albero_t *radice = NULL;
	int       chiave, numero_chiavi, primo_vincolo, secondo_vincolo, contatore;
	int       esito_lettura, acquisizione_errata;

	
	do {
		printf("Inserisci il numero di chiavi > \n");
		esito_lettura = scanf("%d", &numero_chiavi);
		printf("Inserisci il primo vincolo (valore piccolo rispetto al secondo vincolo) > \n");
		esito_lettura = scanf("%d", &primo_vincolo);
		printf("Inserisci il secondo vincolo (valore grande rispetto al primo vincolo) > \n");
		esito_lettura = scanf("%d", &secondo_vincolo);
		acquisizione_errata = esito_lettura != 1 || primo_vincolo >= secondo_vincolo;
		if (acquisizione_errata)
			printf("Errore !\n");
		while (getchar() != '\n');

	} while (acquisizione_errata);
	
	srand(1);
	for (contatore = 0, chiave = rand() % numero_chiavi; (contatore < numero_chiavi); contatore++, chiave = rand() % numero_chiavi)
		creazione_bst(&radice, chiave);
	
	printf("Somma delle chiavi con valori inclusi tra %d e %d : %d\n", primo_vincolo, secondo_vincolo, somma_vincolata(radice, primo_vincolo, secondo_vincolo));

	return (0);


}


/*
 *
 *	@brief Creazione Albero Binario di Ricerca
 *
 * */
void creazione_bst(albero_t **radice, int chiave) {

	albero_t *nodo_n, *nuovo_nodo, *nodo_padre;

	for (nodo_n = nodo_padre = *radice; 
			(nodo_n != NULL && nodo_n->chiave != chiave); 
	     nodo_padre = nodo_n, nodo_n = (chiave < nodo_n->chiave)? nodo_n->figlio_sx : nodo_n->figlio_dx);

	if (nodo_n == NULL) {
		nuovo_nodo = (albero_t *)malloc(sizeof(albero_t));
		nuovo_nodo->chiave = chiave;
		nuovo_nodo->figlio_sx = nuovo_nodo->figlio_dx = NULL;
		if (nodo_n == *radice)
			*radice = nuovo_nodo;
		else 
			if (chiave < nodo_padre->chiave)
				nodo_padre->figlio_sx = nuovo_nodo;
			else
				nodo_padre->figlio_dx = nuovo_nodo;
	}

}

/*
 *
 *	@brief Somma dei valori con vincolo
 *
 * */
int somma_vincolata(albero_t *radice, int primo_vincolo, int secondo_vincolo) {

	int       somma = 0;

	if (radice == NULL) {

		somma = somma_vincolata(radice->figlio_sx, primo_vincolo, secondo_vincolo);
		if (primo_vincolo <= radice->chiave && radice->chiave <= secondo_vincolo)
			somma += radice->chiave;
		somma = somma_vincolata(radice->figlio_dx, primo_vincolo, secondo_vincolo);
	}


	return (somma);
		
}
