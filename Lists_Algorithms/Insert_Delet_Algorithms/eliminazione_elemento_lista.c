/*
*
*	@author Elia Renzoni
*	@date   21/04/2023
*	@brief  Eliminazione di un elemento da una lista singolarmente concatenata
*
**/

#include <stdio.h>
#include <stdlib.h>

#define LIMITE 20

typedef struct elementi {
	int              valore;
	struct elementi *successivo;
} elementi_t;

elementi_t *creazione_lista(void);
int         rimozione_elementi(elementi_t **, int);

int main(void) {

	elementi_t *testa_lista;
	int         elemento_da_rimuovere;
	int         esito_lettura, esito_eliminazione;

	testa_lista = creazione_lista();

	printf("Inserisci un elemento da rimuovere > \n");
	esito_lettura = scanf("%d", &elemento_da_rimuovere);
	esito_eliminazione = rimozione_elementi(&testa_lista, elemento_da_rimuovere);

	if (esito_eliminazione)
		printf("Elemento %d eliminato\n", elemento_da_rimuovere);
	else
		printf("Eelemento %d non eliminato \n", elemento_da_rimuovere);

	free(testa_lista);

	return (0);

}

/*
*
*	@brief creazione lista concatenata
*	@return indirizzo della testa
*
*
**/
elementi_t *creazione_lista(void) {

	elementi_t *oggetto_lista, *testa_lista;
	int         numero, contatore;

	srand(1);
	numero = rand() % LIMITE;
	oggetto_lista = testa_lista = (elementi_t *)malloc(sizeof(elementi_t));
	oggetto_lista->valore = numero;

	for (numero = rand() % LIMITE, contatore = 0; (contatore < LIMITE); contatore++, numero = rand() % LIMITE) {
		oggetto_lista = oggetto_lista->successivo = (elementi_t *)malloc(sizeof(elementi_t));
		oggetto_lista->valore = numero;
	}
	oggetto_lista->successivo = NULL;

	return (testa_lista);

}

/*
*
*	@brief rimozione di un elemento dalla lista
*	@param testa della lista
*	@param valore da rimuovere
*	@return variabile contente l'esito della rimozione
*
**/
int rimozione_elementi(elementi_t **testa_lista, int valore_da_rimuovere) {

	elementi_t *oggetto_lista, *oggetto_precedente;
	int         esito_rimozione;

	for (oggetto_precedente = oggetto_lista = *testa_lista; 
						((oggetto_lista != NULL) && (oggetto_lista->valore != valore_da_rimuovere)); 
								oggetto_precedente = oggetto_lista, oggetto_lista = oggetto_lista->successivo);

	if (oggetto_lista == NULL || oggetto_lista->valore != valore_da_rimuovere)
		esito_rimozione = 0;
	else {

		esito_rimozione = 1;
		if (oggetto_lista == *testa_lista) 
			*testa_lista = oggetto_lista->successivo;
		else 
			oggetto_precedente->successivo = oggetto_lista->successivo;

		free(oggetto_lista);
	}

	return (esito_rimozione);

}