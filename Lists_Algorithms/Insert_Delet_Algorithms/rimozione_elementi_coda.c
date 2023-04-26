/*
*
*	@author Elia Renzoni
*	@date   23/04/2023
*	@brief  Algoritmo di rimozione di elmenti da una coda - ordine FIFO
*
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALORE   30
#define MAX_ELEMENTI 15

typedef struct coda {
	int          valore;
	struct coda  *successivo;
} coda_t;


void    creazione_coda(coda_t **, coda_t **, int);
coda_t *eliminazione_elem_coda(coda_t **, coda_t **);

int main(void) {

	coda_t *uscita, *ingresso, *elem_dele;
	int     numero_ins, numero_elim;
	int     contatore = 0;
	
	uscita = ingresso = NULL;
	srand(time(NULL));
	for (numero_ins = rand() % MAX_VALORE; (contatore < MAX_ELEMENTI); numero_ins = rand() % MAX_VALORE) 
		creazione_coda(&uscita, &ingresso, numero_ins);

	printf("Inserisci il numero di elementi da elminare > \n");
	scanf("%d", &numero_elim);
	for (contatore = 0; (contatore < numero_elim); contatore++) {
		elem_dele = eliminazione_elem_coda(&uscita, &ingresso);
		free(elem_dele);
	}


	return (0);
}

/*
*
*	@brief algoritmo di creazione della coda
*	@param indirizzo punto di uscita
*	@param indirizzo punto di ingresso
*	@param valore da inserire
*
**/
void creazione_coda(coda_t **uscita, coda_t **ingresso, int valore_inserire) {

	coda_t *oggetto_nuovo = (coda_t *)malloc(sizeof(coda_t));
	oggetto_nuovo->valore = valore_inserire;
	oggetto_nuovo->successivo = NULL;

	if (*ingresso != NULL)
		(*ingresso)->successivo = oggetto_nuovo;
	else
		*uscita = oggetto_nuovo;
	*ingresso = oggetto_nuovo;


}

/*
*
*	@brief algoritmo di eliminazione elementi dalla coda
*	@param indirizzo del punto di uscita
*	@param indirizzo del punto di ingresso
*	@return indirzzo dell'oggetto eliminato
*
**/
coda_t *eliminazione_elem_coda(coda_t **uscita, coda_t **ingresso) {

	coda_t *oggetto_lista = *uscita;

	if (*uscita != NULL) {
		*uscita = (*uscita)->successivo;
		if (*uscita == NULL)
			*ingresso = NULL;
	}

	return (oggetto_lista);
}
