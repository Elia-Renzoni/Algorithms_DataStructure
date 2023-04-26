/*
*
*	@author Elia Renzoni
*	@date   23/04/2023
*	@brief Algoritmo per la creazione di uno stack - pila - 
*
**/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VALORE   30
#define MAX_ELEMENTI 15

typedef struct stack {
	int           valore;
	struct stack *successivo;
} stack_t;

void crea_stack(stack_t **, int);
void mostra_stack(stack_t *);

int main(void) {

	stack_t *cima = NULL;
	int      numero, contatore;

	srand(1);
	for (contatore = 0, numero = rand() % MAX_VALORE; (contatore < MAX_ELEMENTI); contatore++, numero = rand() % MAX_VALORE)
		crea_stack(&cima, numero);
	
	mostra_stack(cima);

	return (0);
}

/*
*	@brief algoritmo per la creazione di uno stack
*	@param cima dello stack
*	@param valore da inserire
**/
void crea_stack(stack_t **cima, int valore_inserire) {

	stack_t *nuovo_oggetto = (stack_t *)malloc(sizeof(stack_t));
	nuovo_oggetto->valore = valore_inserire;
	nuovo_oggetto->successivo = *cima;
	*cima = nuovo_oggetto;

}

/*
*	@brief algoritmo per mostare i valori di uno stack
*	@param cima dello stack
**/
void mostra_stack(stack_t *cima_stack) {

	stack_t *oggetto_lista;

	for (oggetto_lista = cima_stack; (oggetto_lista != NULL); oggetto_lista = oggetto_lista->successivo)
		printf("%d\n", oggetto_lista->valore);

}
