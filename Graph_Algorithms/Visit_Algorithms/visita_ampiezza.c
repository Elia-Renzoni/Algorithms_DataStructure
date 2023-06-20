/*
*
*	@author Elia Renzoni
*	@date 19/06/2023
*	@brief algoritmo di visita in ampiezza di un grafo diretto e aciclico
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
	bianco,
	grigio,
	nero
} colore_t;

typedef struct vertici {
	int chiave;
	colore_t colore;
	int distanza;
	struct vertici *vertice_succ;
	struct archi *arco_uscente;
} vertici_t;

typedef struct archi {
	struct vertici *vertice;
	struct archi *arco_succ;
} archi_t;

typedef struct coda_colore {
	vertici_t *chiave;
	struct coda_colore *succ;
} coda_t;

void inserisci_in_lista_prim(vertici_t **, int);
void inserisci_in_lista_sec(archi_t **, int);
void inserisci_in_coda(coda_t **, coda_t **, vertici_t *);
vertici_t *valida_valore(vertici_t *, int);
vertici_t *rimuovi_da_coda(coda_t **, coda_t **);
void avvia_visita_ampiezza(vertici_t *);
void visita_ampiezza(vertici_t *);

int main(int argc, char **argv) {

	vertici_t *testa_lista_prim = NULL, *vertice;
	archi_t *testa_lista_sec = NULL;
	int valore, numero_elem_lista_prim, numero_elem_arc_uscenti, contatore;

	do {
		printf("Inserisci il numero dei vertici > \n");
		scanf("%d", &numero_elem_lista_prim);
		if (numero_elem_lista_prim < 0)
			printf("Errore !\n");
		while (getchar() != '\n');
	} while (numero_elem_lista_prim < 0);

	srand(time(NULL));
	for (contatore = 0; (contatore < numero_elem_lista_prim); contatore++) {
		valore = rand();
		inserisci_in_lista_prim(&testa_lista_prim, valore);
	}
	for (vertice = testa_lista_prim; (vertice != NULL); vertice = vertice->vertice_succ) {
		do {
			printf("Inserisci il numero di archi uscenti > \n");
			scanf("%d", &numero_elem_arc_uscenti);
			if (numero_elem_arc_uscenti < 0)
				printf("Errore \n");
			while (getchar() != '\n');
		} while (numero_elem_arc_uscenti < 0);

		for (contatore = 0; (contatore < numero_elem_arc_uscenti); contatore++) {
			valore = rand();
			if (valida_valore(testa_lista_prim, valore) != NULL)
				inserisci_in_lista_sec(&testa_lista_sec, valore);
		}
		vertice->arco_uscente = testa_lista_sec;
		testa_lista_sec = NULL;
	}
	avvia_visita_ampiezza(testa_lista_prim);

	return (0);
}

void inserisci_in_lista_prim(vertici_t **testa, int valore) {

	vertici_t *nuovo_vertice, *vertice_gen, *vertice_prec;

	for (vertice_prec = vertice_gen = *testa; 
						(vertice_gen != NULL && vertice_gen->chiave != valore); 
						vertice_prec = vertice_gen,	vertice_gen = vertice_gen->vertice_succ);
	if (vertice_gen == NULL) {
		nuovo_vertice = (vertici_t *)malloc(sizeof(vertici_t));
		nuovo_vertice->chiave = valore;
		nuovo_vertice->arco_uscente = NULL;
		nuovo_vertice->vertice_succ = NULL;
		if (vertice_gen == *testa) 
			*testa = nuovo_vertice;
		else
			vertice_prec->vertice_succ = nuovo_vertice;
	}
}

void inserisci_in_lista_sec(archi_t **testa, int valore) {

	archi_t *nuovo_arco, *arco_gen, *arco_prec;

	for (arco_prec = arco_gen = *testa; (arco_gen != NULL); arco_prec = arco_gen, arco_gen = arco_gen->arco_succ);

	if (arco_gen == NULL) {
		nuovo_arco = (archi_t *)malloc(sizeof(archi_t));
		nuovo_arco->vertice = (vertici_t *)malloc(sizeof(vertici_t));
		nuovo_arco->vertice->chiave = valore;
		nuovo_arco->arco_succ = NULL;
		if (arco_gen == *testa) 
			*testa = nuovo_arco;
		else
			arco_prec->arco_succ = nuovo_arco;
	}
}

void inserisci_in_coda(coda_t **uscita, coda_t **ingresso, vertici_t *vertice_grafo) {

	coda_t *nuovo_elem = (coda_t *)malloc(sizeof(coda_t));
	nuovo_elem->chiave = vertice_grafo;
	nuovo_elem->succ = NULL;
	if (*ingresso != NULL)
		(*ingresso)->succ = nuovo_elem;
	else
		*uscita = nuovo_elem;
	*ingresso = nuovo_elem;
}

vertici_t *valida_valore(vertici_t *testa_lista, int valore_cercare) {

	vertici_t *vertice;

	for (vertice = testa_lista; (vertice != NULL && vertice->chiave != valore_cercare); vertice = vertice->vertice_succ);

	return (vertice);
}

vertici_t *rimuovi_da_coda(coda_t **uscita, coda_t **ingresso) {

	vertici_t *elem_rem = (vertici_t *)*uscita;
	if (*uscita != NULL) {
		*uscita = (*uscita)->succ;
		if (*uscita == NULL)
			*ingresso = NULL;
	}
	return (elem_rem);
}

void avvia_visita_ampiezza(vertici_t *testa_lista_prim) {

	vertici_t *vertice;

	for (vertice = testa_lista_prim; (vertice != NULL); vertice = vertice->vertice_succ) {
		vertice->distanza = -1;
		vertice->colore = bianco;
	}

	for (vertice = testa_lista_prim; (vertice != NULL); vertice = vertice->vertice_succ) {
		if (vertice->colore == bianco)
			visita_ampiezza(vertice);
	}
}

void visita_ampiezza(vertici_t *vertice_sorgente) {

	vertici_t *vertice;
	archi_t *arco;
	coda_t *uscita = NULL, *ingresso = NULL;

	vertice_sorgente->colore = grigio;
	vertice_sorgente->distanza = 0;
	inserisci_in_coda(&uscita, &ingresso, vertice_sorgente);

	while (uscita != NULL) {
		vertice = rimuovi_da_coda(&uscita, &ingresso);
		printf("%d\n", vertice->chiave);
		for (arco = vertice->arco_uscente; (arco != NULL); arco = arco->arco_succ) {
			if (arco->vertice->colore == bianco) {
				arco->vertice->colore = grigio;
				arco->vertice->distanza = vertice->distanza + 1;
				inserisci_in_coda(&uscita, &ingresso, arco->vertice);
			}
		}
		vertice->colore = nero;
	}
}
