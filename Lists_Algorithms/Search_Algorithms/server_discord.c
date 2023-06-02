/*
 *
 *	@author Elia Renzoni
 *	@date 02/06/2023
 *	@brief implementazione di una coda per gestire il server discord, gestione degli accessi a un canale discord, secondo un ordine di priorita
 *
 * */

#include <stdio.h>
#include <stdlib.h>

#define NUMERO_RICH 45

typedef struct {
	int id_utente, data_richiesta;
} utente_t;

typedef struct coda_richieste {
	utente_t chiave;
	struct coda_richieste *succ;
} coda_richieste_t;

void invia_richiesta(coda_richieste_t **, coda_richieste_t **, int, int);
coda_richieste_t *cerca_richiesta(coda_richieste_t *, int, int *);
coda_richieste_t *rimozione_richiesta(coda_richieste_t **, coda_richieste_t **);
void heap_sort(utente_t *, int);
void setaccia_heap(utente_t *, int, int);

int main(void) {

	coda_richieste_t *uscita = NULL, *ingresso = NULL, *prio_richiesta, *richiesta_acc;
	int contatore, esito_lettura, acquisizione_errata, id_utente, posizione = 0;
	utente_t *richieste_accesso;

	do {
		printf("Inserisci il tuo id per scoprire lo stato della richiesta > \n");
		esito_lettura = scanf("%d", &id_utente);
		acquisizione_errata = esito_lettura != 1 || id_utente < 1;
		if (acquisizione_errata)
			printf("Errore !\n");
		while (getchar() != '\n');
	} while (acquisizione_errata);

	richieste_accesso = (utente_t *)calloc(NUMERO_RICH + 1, sizeof(utente_t));
	srand(1);
	for (contatore = 1; (contatore <= NUMERO_RICH); contatore++) {
		richieste_accesso[contatore].id_utente = rand() % NUMERO_RICH;
		richieste_accesso[contatore].data_richiesta = rand() % (NUMERO_RICH * NUMERO_RICH);
	}
	heap_sort(richieste_accesso, NUMERO_RICH);

	for (contatore = NUMERO_RICH; (contatore >= 1); contatore--)
		invia_richiesta(&uscita, &ingresso, richieste_accesso[contatore].id_utente, richieste_accesso[contatore].data_richiesta);
	
	prio_richiesta = cerca_richiesta(uscita, id_utente, &posizione);
	printf("Priorita' della richiesta > %d, Posizione richiesta > %d \n", prio_richiesta->chiave.data_richiesta, posizione);
	richiesta_acc = rimozione_richiesta(&uscita, &ingresso);
	printf("Richiesta accettata per l'elemento > %d \n", richiesta_acc->chiave.id_utente);

	return (0);

}

void invia_richieste(coda_richieste_t **uscita, coda_richieste_t **ingresso, int id_utente, int data_rich) {

	coda_richieste_t *nuovo_elem = (coda_richieste_t *)malloc(sizeof(coda_richieste_t));
	nuovo_elem->chiave.id_utente = id_utente;
	nuovo_elem->chiave.data_richiesta = data_rich;
	nuovo_elem->succ = NULL;
	if (*ingresso != NULL) 
		(*ingresso)->succ = nuovo_elem;
	else
		*uscita = nuovo_elem;
		
	*ingresso = nuovo_elem;
}

coda_richieste_t *cerca_richiesta(coda_richieste_t *uscita, int id_utente, int *posizione) {

	coda_richieste_t *elem;

	for (elem = uscita; (elem != NULL && elem->chiave.id_utente != id_utente); elem = elem->succ)
		++posizione;

	return (elem);
}

coda_richieste_t *rimozione_richiesta(coda_richieste_t **uscita, coda_richieste_t **ingresso) {

	coda_richieste_t *elem_rim = *uscita;
	if (*uscita != NULL) {
		*uscita = (*uscita)->succ;
		if (*uscita == NULL) 
			*ingresso = NULL;
	}

	return (elem_rim);
}

void heap_sort(utente_t *richieste, int numero_elementi) {
	
	int sx, dx, tmp;

	for (sx = numero_elementi / 2; (sx >= 1); sx--)
		setaccia_heap(richieste, sx, numero_elementi);
	for (dx = numero_elementi; (dx > 1); dx--) {
		tmp = richieste[1].data_richiesta;
		richieste[1].data_richiesta = richieste[dx].data_richiesta;
		richieste[dx].data_richiesta = tmp;
		setaccia_heap(richieste, 1, dx - 1);
	}
}

void setaccia_heap(utente_t *richieste, int sx, int dx) {

	int nuovo_valore, i, j;

	for (nuovo_valore = richieste[sx].data_richiesta, i = sx, j = 2 * i; (j <= dx);) {
		if ((j <= dx) && (richieste[j + 1].data_richiesta > richieste[j].data_richiesta))
			j++;
		if (nuovo_valore < richieste[j].data_richiesta) {
			richieste[i].data_richiesta = richieste[j].data_richiesta;
			i = j;
			j = 2 * i;
		}
		else
			j = dx + 1;
	}
	if (sx != i) {
		richieste[i].data_richiesta = nuovo_valore;
	}

}


