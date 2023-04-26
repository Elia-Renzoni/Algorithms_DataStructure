/*
*
*	@author Elia Renzoni
*	@date   23/04/2023
*	@brief  Eliminazione dati in ordine LIFO da uno stack
*
**/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VALORE   50
#define MAX_ELEMENTI 45

typedef struct stack {
	int           valori;
	struct stack *successivo;
} stack_t;

void     creazione_stack(stack_t **, int);
stack_t *elminazione_elem_stack(stack_t **);

int main(void) {

	stack_t *cima = NULL, *elem_dele;
	int      numeri, contatore, elementi_elim;

	srand(1);
	for (contatore = 0, numeri = rand() % MAX_VALORE; (contatore < MAX_ELEMENTI); contatore++, numeri = rand() % MAX_VALORE)
		creazione_stack(&cima, numeri);

	printf("Inserisci il numero di elementi da eliminare (<= 45) \n");
	scanf("%d", &elementi_elim);
	for (contatore = 0; (contatore < elementi_elim); contatore++) {
		elem_dele = elminazione_elem_stack(&cima);
		free(elem_dele);
	}

	return (0);
}

/*
*	@brief algoritmo per la creazione di uno stack
*	@param indirizzo della cima
*	@param valore da inserire
**/
void creazione_stack(stack_t **cima, int valore_inserire) {

	stack_t *nuovo_oggetto = (stack_t *)malloc(sizeof(stack_t));
	nuovo_oggetto->valori = valore_inserire;
	nuovo_oggetto->successivo = *cima;
	*cima = nuovo_oggetto;

}

/*
*	@brief algoritmo per la rimozione di n valori dallo stack
*	@param indirizzo della cima
*       @return indirizzo dell'elemento da eliminare
**/
stack_t *elminazione_elem_stack(stack_t **cima) {

	stack_t *oggetto_elimi = *cima;
	if (*cima != NULL)
		*cima = (*cima)->successivo;

	return (oggetto_elimi);

}
