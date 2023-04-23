/*
*
*	@author Elia Renzoni
*	@date   23/04/2023
*	@brief  Algoritmo di ricerca di un valore all'interno di una lista sing. concat.
*
**/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VALORE 	 20
#define MAX_ELEMENTS 15

typedef struct elem {
	int          numeri;
	struct elem *successore;
} elem_t;

elem_t *creazione_lista(void);
elem_t *ricerca_inlista(elem_t *, int);

int main(void) {

	elem_t *testa_lista, *esito_ricerca;
	int     valore_da_ricercare;

	testa_lista = creazione_lista();
	if (testa_lista != NULL) {
		printf("Inserisci un valore da ricercare (<= 20) \n");
		scanf("%d", &valore_da_ricercare);
		esito_ricerca = ricerca_inlista(testa_lista, valore_da_ricercare);
		if (esito_ricerca != NULL) 
			printf("Valore Trovato ! \n");
		else
			printf("Valore non Trovato ! \n");
	}
	else
		printf("Lista vouta ! \n");

	free(testa_lista);

	return (0);
}

/*
*
*	@brief Creazione lista concatenata
*	@return indirizzo della testa
*
**/
elem_t *creazione_lista(void) {

	elem_t *oggetto_lista, *testa_lista;
	int     numero_gen, contatore = 0;

	srand(1);
	numero_gen = rand() % MAX_VALORE;
	oggetto_lista = testa_lista = (elem_t *)malloc(sizeof(elem_t));
	oggetto_lista->numeri = numero_gen;

	for (numero_gen = rand() % MAX_VALORE; (contatore < MAX_ELEMENTS); numero_gen = rand() % MAX_VALORE, contatore++) {
		oggetto_lista = oggetto_lista->successore = (elem_t *)malloc(sizeof(elem_t));
		oggetto_lista->numeri = numero_gen;
	}
	oggetto_lista->successore = NULL;

	return (testa_lista);
}

/*
*
*	@brief Algo di ricerca su una lista sing. concat.
*	@param Testa Lista
*	@param Valore da ricercare
*	@return indirizzo dell'oggetto lista l-esimo
*
**/
elem_t *ricerca_inlista(elem_t *testa_lista, int valore_ricercare) {

	elem_t *oggetto_lista;

	for (oggetto_lista = testa_lista; 
		 (oggetto_lista != NULL && oggetto_lista->numeri != valore_ricercare); 
		  oggetto_lista = oggetto_lista->successore);

	return (oggetto_lista);
}
