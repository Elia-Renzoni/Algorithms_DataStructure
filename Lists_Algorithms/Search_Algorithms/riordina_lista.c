/*
 *
 *	@author Elia Renzoni
 *	@date 08/05/2023
 *	@brief creazione di un algoritmo che crei una lista sing. concat con n elementi pari al numero i-esimo dello stallo, e inverta gli elemnti con attributi pari, restituendo la nuova testa
 *
 *
 **/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>


#define CONTROLLO_PARI 2


typedef struct lista {
	int           numeri;
	struct lista *successivo;
} lista_t;

void creazione_lista(lista_t **, int);
void visita_lista(lista_t *);
void creazione_nuova_lista(lista_t *);
void visita_nuova_lista(lista_t *);

int main(void) {

	lista_t *testa_lista = NULL;
	int      numero_stalli, contatore, valore_inserire, supporto;
	int      esito_lettura, acquisizione_errata;

	do {
		printf("Inserisci il numero degli stalli > \n");
		esito_lettura = scanf("%d", &numero_stalli);

		acquisizione_errata = esito_lettura != 1 || numero_stalli < 1 || numero_stalli > (INT_MAX / 4);
		if (acquisizione_errata) 
			printf("Errore, ripeti l'azione !\n");
		while (getchar() != '\n');

	} while (acquisizione_errata);

	srand(time(NULL));
	for (contatore = 0; (contatore <= numero_stalli); contatore++) {
		supporto = 0;
		while (contatore >= supporto) {
			valore_inserire = rand() % (numero_stalli * numero_stalli);
			creazione_lista(&testa_lista, valore_inserire);
			++supporto;
		}
	}

	printf("Prima Lista > \n");
	visita_lista(testa_lista);

	printf("Creazione Seconda Lista > \n");
	creazione_nuova_lista(testa_lista);
	visita_nuova_lista(testa_lista);


	return (0);


}

/*
 *	@brief creazione della lista sing. concat
 *	
 * */
void creazione_lista(lista_t **testa_lista, int chiave) {

	lista_t *nuovo_oggetto, *oggetto_lesimo, *oggetto_prec;

	for (oggetto_prec = oggetto_lesimo = *testa_lista; 
		(oggetto_lesimo != NULL && oggetto_lesimo->numeri < chiave);
	     oggetto_prec = oggetto_lesimo, oggetto_lesimo = oggetto_lesimo->successivo);

	if (oggetto_lesimo == NULL || oggetto_lesimo->numeri > chiave) {
		nuovo_oggetto = (lista_t *)malloc(sizeof(lista_t));
		nuovo_oggetto->numeri = chiave;
		nuovo_oggetto->successivo = oggetto_lesimo;
		if (oggetto_lesimo == *testa_lista)
			*testa_lista = nuovo_oggetto;
		else
			oggetto_prec->successivo = nuovo_oggetto;
	}

}

/*
 *	@brief creazione della nuova lista - inverto i valori pari
 *
 * */
void creazione_nuova_lista(lista_t *testa_lista) {

	lista_t *oggetto_lista, *oggetto_prec;
	int      tmp;

	for (oggetto_prec = oggetto_lista = testa_lista; (oggetto_lista != NULL); oggetto_prec = oggetto_lista, oggetto_lista = oggetto_lista->successivo) {
		if (oggetto_lista->numeri % CONTROLLO_PARI == 0) {
			tmp = oggetto_prec->numeri;
			oggetto_prec->numeri = oggetto_lista->numeri;
			oggetto_lista->numeri = tmp;
		}
	}

}

/*
 *	@brief visita della prima lista
 *
 * */
void visita_lista(lista_t *testa_lista) {

	lista_t *oggetto_lista;

	for (oggetto_lista = testa_lista; (oggetto_lista != NULL); oggetto_lista = oggetto_lista->successivo)
		printf("%d\n", oggetto_lista->numeri);

}

/*
 *	@brief visita della seconda lista
 *
 * */
void visita_nuova_lista(lista_t *testa_lista) {
	
	lista_t *oggetto_lista;

	for (oggetto_lista = testa_lista; (oggetto_lista != NULL); oggetto_lista = oggetto_lista->successivo)
		printf("%d\n", oggetto_lista->numeri);

}


