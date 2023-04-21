/*
*
*	@author Elia Renzoni
*	@brief  Data una lista singolarmente concatenata, creazione di una lista contente gli elementi dispari, se questi hanno il successivo pari
*	@date 20/04/2023
*
*
**/

#include <stdio.h>
#include <stdlib.h>

#define SENTINELLA 00

typedef struct numeri {
	int            numero;
	struct numeri *successivo;
} numeri_t;

numeri_t *creazione_lista(void);
numeri_t *divisione_lista(numeri_t *);
void      mostra_nuova_lista(numeri_t *);

int main(void) {

	numeri_t *testa_lista, *testa_nuova_lista;

	testa_lista = creazione_lista();
	if (testa_lista != NULL) {
		testa_nuova_lista = divisione_lista(testa_lista);
	
		if (testa_nuova_lista != NULL)
			mostra_nuova_lista(testa_nuova_lista);
		else
			printf("Lista non creata !\n");
	}
	else 
		printf("Lista non creata !\n");
	
	free(testa_lista);
	free(testa_nuova_lista);

	return (0);
}

/*
*
*	@brief creazione lista sing. concatenata
**/
numeri_t *creazione_lista(void) {

	numeri_t *oggetto_lista, *testa_lista;
	int       valore_da_inserire;

	printf("Inserisci dei valori, quando vuoi fermarti inserisci 00 \n");
	scanf("%d", &valore_da_inserire);
	if (valore_da_inserire != SENTINELLA) {
		testa_lista = oggetto_lista = (numeri_t *)malloc(sizeof(numeri_t));
		oggetto_lista->numero = valore_da_inserire;
		for (scanf("%d", &valore_da_inserire); (valore_da_inserire != SENTINELLA); scanf("%d", &valore_da_inserire)) {
			oggetto_lista = oggetto_lista->successivo = (numeri_t *)malloc(sizeof(numeri_t));
			oggetto_lista->numero = valore_da_inserire;
		}
		oggetto_lista->successivo = NULL;
	}
	else
		testa_lista = NULL;

	return (testa_lista);

}

/*
*
*	@brief creazione della nuova lista
*	@param *testa_lista => testa della lista precedente
*   @return testa_nuova_lista => indirizzo della testa della nuova lista	
*
**/
numeri_t *divisione_lista(numeri_t *testa_lista) {

	numeri_t *oggetto_lista, *testa_nuova_lista, *nuovo_oggetto_lista, *oggetto_lista_precedente;
	int       valore_dispari, contatore = 0;

	for (oggetto_lista = testa_lista; (oggetto_lista != NULL); oggetto_lista = oggetto_lista_precedente->successivo) {
		if (oggetto_lista->numero % 2 != 0) {
			valore_dispari = oggetto_lista->numero;
			oggetto_lista_precedente = oggetto_lista;
			oggetto_lista = oggetto_lista->successivo;
			if (oggetto_lista->numero % 2 == 0) {
				contatore++;
				if (contatore == 1) {
					nuovo_oggetto_lista = testa_nuova_lista = (numeri_t *)malloc(sizeof(numeri_t));
					testa_nuova_lista->numero = valore_dispari;
					nuovo_oggetto_lista = nuovo_oggetto_lista->successivo = (numeri_t *)malloc(sizeof(numeri_t));
				}
				else {
					nuovo_oggetto_lista->numero = valore_dispari;
					nuovo_oggetto_lista = nuovo_oggetto_lista->successivo = (numeri_t *)malloc(sizeof(numeri_t));
				}
			}

		}
		else
			oggetto_lista_precedente = oggetto_lista;

	}

	if (contatore == 0)
		testa_nuova_lista = NULL;
	else if (contatore == 1 || contatore > 1)
		nuovo_oggetto_lista->successivo = NULL;

	return (testa_nuova_lista);

}

/*
*
*	@brief sottoprogramma per stampare la nuova lista
*   @param testa della nuova lista
*
**/
void mostra_nuova_lista(numeri_t *testa_lista) {

	numeri_t *oggetto_lista;

	for (oggetto_lista = testa_lista; (oggetto_lista != NULL); oggetto_lista = oggetto_lista->successivo)
		printf("%d\n", oggetto_lista->numero);

}
