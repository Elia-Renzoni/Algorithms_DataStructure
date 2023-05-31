/*
*	@author Elia Renzoni
*	@date 30/05/2023
*	@brief dato un array di interi, trovare il massimo di un sottoarray (tre elementi) e scriverlo in una coda
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct coda {
	int chiave;
	struct coda *succ;
} coda_t;

int cerca_massimo_locale(int *, int, int, int);
void crea_coda(coda_t **, coda_t **, int);
void mostra_coda(coda_t *);

int main(void) {

	coda_t *ingresso = NULL, *uscita = NULL;
	int valore, numero_elementi, contatore, acquisizione_errata, indice_movimento, indice, massimo_locale;
	int *sequenza_numeri = NULL;

	do {
		printf("Inserisci il numero degli elementi > \n");
		scanf("%d", &numero_elementi);
		printf("Inserisci l'indice di movimento > \n");
		scanf("%d", &indice_movimento);
		acquisizione_errata = indice_movimento < 1 || indice_movimento >= INT_MAX || numero_elementi < 1 || numero_elementi >= (INT_MAX / 4);
		if (acquisizione_errata)
			printf("Errore !\n");
		while (getchar() != '\n');
	} while (acquisizione_errata);

	sequenza_numeri = (int *)calloc(numero_elementi, sizeof(int));
	if (sequenza_numeri != NULL) {
		srand(time(NULL));
		for (contatore = 0; (contatore < numero_elementi); contatore++) {
			valore = rand() %  (numero_elementi * numero_elementi);
			sequenza_numeri[contatore] = valore;
		}
		for (contatore = 0; (contatore < numero_elementi); contatore++) {
			massimo_locale = cerca_massimo_locale(sequenza_numeri, contatore, contatore + indice_movimento, indice_movimento);
			crea_coda(&uscita, &ingresso, massimo_locale);
		}
		mostra_coda(uscita);
	}
	else 
		printf("Impossibile allocare l'array ! \n");

	free(sequenza_numeri);
	free(uscita);
	free(ingresso);

	return (0);

}

int cerca_massimo_locale(int *sequenza_numeri, int posizione_sx, int posizione_dx, int indice_movimento) {

	int massimo;
	int contatore, posizione_partenza;

	for (posizione_partenza = posizione_sx, contatore = 0; (contatore < indice_movimento); posizione_partenza++, contatore++) {
		if (sequenza_numeri[posizione_partenza] < sequenza_numeri[posizione_partenza + 1])
			massimo = sequenza_numeri[posizione_partenza];
		else
			massimo = sequenza_numeri[posizione_partenza];
	}

	return (massimo);

}

void crea_coda(coda_t **uscita, coda_t **ingresso, int valore_ins) {

	coda_t *nuovo_elem = (coda_t *)malloc(sizeof(coda_t));
	nuovo_elem->chiave = valore_ins;
	nuovo_elem->succ = NULL;
	if (*ingresso != NULL)
		(*ingresso)->succ = nuovo_elem;
	else
		*uscita = nuovo_elem;
	*ingresso = nuovo_elem;

}

void mostra_coda(coda_t *uscita) {

	coda_t *elem;

	printf("Valori Massimi Locali > \n");
	for (elem = uscita; (elem != NULL); elem = elem->succ)
		printf("%d\n", elem->chiave);

}
