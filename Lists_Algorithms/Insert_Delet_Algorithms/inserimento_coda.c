/*
*
*	@author Elia Renzoni
*   @date   23/04/2023
*	@brief  Algoritmo che implementa una coda
*
*
**/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VALORE_MAX      30
#define NUMERO_ELEM_MAX 20

typedef struct coda {
	int        	 valore;
	struct coda  *successivo;
} coda_t;

void creazione_coda(coda_t **, coda_t **);
void mostra_coda(coda_t *, coda_t *);

int main(void) {

	coda_t *uscita, *ingresso;
	clock_t tempo_creazione_i, tempo_creazione_e, tempo_mostra_i, tempo_mostra_e;
	double  temp_es_creazione, tempo_es_mostra;

	printf("Creazione Coda ! \n");
 
	tempo_creazione_i = clock();
	creazione_coda(&uscita, &ingresso);
	tempo_creazione_e = clock();

	temp_es_creazione = (double)(tempo_creazione_i - tempo_creazione_e) / CLOCKS_PER_SEC;
	printf("Tempo esecuzione creazione coda > %f\n", temp_es_creazione);

	printf("Coda : \n");
	tempo_mostra_i = clock();
	mostra_coda(uscita, ingresso);
	tempo_mostra_e = clock();

	tempo_es_mostra = (double)(tempo_mostra_i - tempo_mostra_e) / CLOCKS_PER_SEC;
	printf("Tempo esecuzione mostra coda > %f\n", tempo_es_mostra);

	return (0);
}

/*
*
*	@brief Algo di creazione di una coda
*	@param indirizzo punto di uscita - head -
*	@param indirizzo punto di ingresso - tail -
*
**/
void creazione_coda(coda_t **uscita, coda_t **ingresso) {

	coda_t *nuovo_oggetto;
	int     numero, contatore;

	srand(1);
	for (contatore = 0, numero = rand() % VALORE_MAX; (contatore < NUMERO_ELEM_MAX); contatore++, numero = rand() % VALORE_MAX) {
		nuovo_oggetto = (coda_t *)malloc(sizeof(coda_t));
		nuovo_oggetto->valore = numero;
		nuovo_oggetto->successivo = NULL;
		if (*ingresso != NULL) 
			(*ingresso)->successivo = nuovo_oggetto;
		else
			*uscita = nuovo_oggetto;
		*ingresso = nuovo_oggetto;
	}

}

/*
*
*	@brief algoritmo di visita della coda
*	@param indirizzo della testa
*
*
**/
void mostra_coda(coda_t *uscita, coda_t *ingresso) {

	coda_t *oggetto_lista;

	for (oggetto_lista = uscita; (oggetto_lista != NULL); oggetto_lista = oggetto_lista->successivo)
		printf("%d\n", oggetto_lista->valore);


}