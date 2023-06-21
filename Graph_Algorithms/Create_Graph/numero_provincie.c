/*
*
*	@author Elia Renzoni
*	@date 21/06/2023
*	@brief creazione di un grafo contente gli id di una citta'
*	dato un arco uscente, se i vertici hanno archi uscenti, allora
*	sono collegati indirettamente e formano una provincia, altrimenti no.
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE  1
#define FALSE 0

typedef struct vertici {
	int id_citta;
	struct vertici *vertice_succ;
	struct archi *archi_uscenti;
} vertici_t;

typedef struct archi {
	struct vertici *vertice;
	struct archi *arco_succ;
} archi_t;

void inserisci_lista_prim(vertici_t **, int);
void inserisci_lista_sec(archi_t **, int);
vertici_t *controlla_valore(vertici_t *, int);
int controlla_provincia(vertici_t *);
int cerca_in_grafo(vertici_t *, int);

int main(void) {

	vertici_t *testa_lista_prim = NULL, *vertice;
	archi_t *testa_lista_sec = NULL;
	int valore, numero_vertici, numero_archi, contatore, numero_provincie;

	do {
		printf("Inserisci il numero dei veritic > \n");
		scanf("%d", &numero_vertici);
		if (numero_vertici < 0)
			printf("Errore !\n");
		while (getchar() != '\n');
	} while (numero_vertici < 0);

	srand(time(NULL));
	for (contatore = 0; (contatore < numero_vertici); contatore++) {
		valore = rand() % 100;
		inserisci_lista_prim(&testa_lista_prim, valore);
	}
	for (vertice = testa_lista_prim; (vertice != NULL); vertice = vertice->vertice_succ) {
		do {
			printf("Inserisci numero archi > \n");
			scanf("%d", &numero_archi);
			if (numero_archi < 0)
				printf("Errore !\n");
			while (getchar() != '\n');
		} while (numero_archi < 0);
		srand(time(NULL));
		for (contatore = 0; (contatore < numero_archi); contatore++) {
			valore = rand() % 100;
			if (controlla_valore(testa_lista_prim, valore) != NULL)
				inserisci_lista_sec(&testa_lista_sec, valore);
		}
		vertice->archi_uscenti = testa_lista_sec;
		testa_lista_sec = NULL;
	}
	printf("Numero di Provincie > %d\n", controlla_provincia(testa_lista_prim));
	free(testa_lista_prim);
	free(testa_lista_sec);

	return (0);
}

void inserisci_lista_prim(vertici_t **testa_lista, int citta_ins) {

	vertici_t *nuovo_vertice, *vertice_gen, *vertice_prec;

	for (vertice_prec = vertice_gen = *testa_lista; (vertice_gen != NULL); vertice_prec = vertice_gen, vertice_gen = vertice_gen->vertice_succ);

	if (vertice_gen == NULL) {
		nuovo_vertice = (vertici_t *)malloc(sizeof(vertici_t));
		nuovo_vertice->id_citta = citta_ins;
		nuovo_vertice->vertice_succ = NULL;
		if (vertice_gen == *testa_lista) 
			*testa_lista = nuovo_vertice;
		else
			vertice_prec->vertice_succ = nuovo_vertice;
	}
}

void inserisci_lista_sec(archi_t **testa_lista, int citta_ins) {

	archi_t *nuovo_arco, *arco_gen, *arco_prec;

	for (arco_prec = arco_gen = *testa_lista; (arco_gen != NULL); arco_prec = arco_gen, arco_gen = arco_gen->arco_succ);

	if (arco_gen == NULL) {
		nuovo_arco = (archi_t *)malloc(sizeof(archi_t));
		nuovo_arco->vertice = (vertici_t *)malloc(sizeof(vertici_t));
		nuovo_arco->vertice->id_citta = citta_ins;
		nuovo_arco->arco_succ = NULL;
		if (arco_gen == *testa_lista)
			*testa_lista = nuovo_arco;
		else
			arco_prec->arco_succ = nuovo_arco;
	}
}

vertici_t *controlla_valore(vertici_t *testa_lista, int valore_cerc) {

	vertici_t *vertice;

	for (vertice = testa_lista; (vertice != NULL && vertice->id_citta != valore_cerc); vertice = vertice->vertice_succ);

	return (vertice);
}

int controlla_provincia(vertici_t *testa_lista) {

	vertici_t *vertice;
	archi_t *arco;
	int numero_province;

	for (vertice = testa_lista; (vertice != NULL); vertice = vertice->vertice_succ) {
		for (arco = vertice->archi_uscenti; (arco != NULL); arco = arco->arco_succ) 
			if (cerca_in_grafo(testa_lista, arco->vertice->id_citta) != FALSE)
				numero_province += 1;
	}

	return (numero_province);
}

int cerca_in_grafo(vertici_t *testa_lista, int citta_cerc) {

	vertici_t *vertice;
	archi_t *arco;

	for (vertice = testa_lista; (vertice != NULL && vertice->id_citta != citta_cerc); vertice = vertice->vertice_succ) 
		for (arco = vertice->archi_uscenti; (arco != NULL && arco->vertice->id_citta != citta_cerc); arco = arco->arco_succ);

	return ((vertice != NULL || arco != NULL)? TRUE : FALSE);
}
