/*
*
*	@author Elia Renzoni
*	@date 11/06/2023
*	@brief prelevare dati da un sensore di umiditá del terreno, e memorizzarlo su una coda
*   leggere i valori e se questo e' rilevante, ovvero se il suo logaritmo é maggiore di 5
*	allora scriverlo su un file ed eliminarli dalla coda.
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_ITER 50
#define MAX_VALUE_GEN_UMIDITA 200
#define MAX_VALUE_DATA_GEN 120
#define ALLARM_SITU 5

enum {
	FALSE,
	TRUE
};

typedef struct {
	int valore_umidita;
	int data;
} val_sensori_t;

typedef struct coda_dati {
	val_sensori_t chiave;
	struct coda_dati *succ;
} coda_dati_t;

val_sensori_t acquisisci_valore(void);
int inserisci_in_coda(coda_dati_t **, coda_dati_t **, int, int);
coda_dati_t *preleva_dati_coda(coda_dati_t **, coda_dati_t **);
void smista_dati(int, int, FILE *);

int main(void) {

	FILE *file_risposta;
	coda_dati_t *ingresso = NULL, *uscita = NULL, *elem;
	val_sensori_t valori_sensori;
	int contatore, esito_inserimento;

	file_risposta = fopen("dati_rilevanti.txt", "w");
	if (file_risposta != NULL) {
		for (contatore = 0; (contatore < MAX_ITER); contatore++) {
			valori_sensori = acquisisci_valore();
			esito_inserimento = inserisci_in_coda(&uscita, &ingresso, valori_sensori.valore_umidita, valori_sensori.data);
			if (esito_inserimento)
				printf("%d\n", TRUE);
			else
				printf("%d\n", FALSE);
		}
		for (contatore = 0; (contatore < MAX_ITER); contatore++) {
			elem = preleva_dati_coda(&uscita, &ingresso);
			smista_dati(elem->chiave.valore_umidita, elem->chiave.data, file_risposta);
			if (elem != NULL)
				free(elem);
		}
	}
	else
		exit(-1);

	return (0);

}

val_sensori_t acquisisci_valore(void) {

	val_sensori_t coppia_dati_sensore;
	srand(time(NULL));
	coppia_dati_sensore.valore_umidita = rand() % MAX_VALUE_GEN_UMIDITA;
	coppia_dati_sensore.data = rand() % MAX_VALUE_DATA_GEN;
	return (coppia_dati_sensore);

}

int inserisci_in_coda(coda_dati_t **uscita, coda_dati_t **ingresso, int umidita, int data) {

	coda_dati_t *nuovo_elem = (coda_dati_t *) malloc(sizeof(coda_dati_t));
	nuovo_elem->chiave.valore_umidita = umidita;
	nuovo_elem->chiave.data = data;
	nuovo_elem->succ = NULL;
	if (*ingresso != NULL) 
		(*ingresso)->succ = nuovo_elem;
	else
		*uscita = nuovo_elem;
	*ingresso = nuovo_elem;

}

coda_dati_t *preleva_dati_coda(coda_dati_t **uscita, coda_dati_t **ingresso) {

	coda_dati_t *elem_eliminare = *uscita;
	if (*uscita != NULL) {
		*uscita = (*uscita)->succ;
		if (*uscita == NULL)
			*ingresso = NULL;
	}
	return (elem_eliminare);

}

void smista_dati(int umidita, int data_prelievo, FILE *file_risposta) {

	if (log(umidita) > ALLARM_SITU) 
		fprintf(file_risposta, "Umidita %d - Data %d \n", umidita, data_prelievo);

}