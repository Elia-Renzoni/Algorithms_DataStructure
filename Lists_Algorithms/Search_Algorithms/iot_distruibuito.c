/*
 *
 *	@author Elia Renzoni
 *	@date 04/06/2023
 *	@brief inserire in uno stack i dati provenienti dai sensori in una rete e ordinarli se lo stack ha piu di un elemento
 * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define LIMITE_INF 3

typedef struct PilaDataSens {
	int Valore;
	struct PilaDataSens *Succ;
} PilaDataSens_t;

void InserisciInPila(PilaDataSens_t **, int);
PilaDataSens_t *RimuoviDaPila(PilaDataSens_t **);
void HeapSort(int *, int);
void SetacciaHeap(int *, int , int);
void VisitaArray(int *, int);

int main(void) {

	PilaDataSens_t *Cima = NULL;
	int Valore, NumeroElem, Contatore, EsitoLettura, AcqErr;
	int *ValoriOrdinati = NULL;

	do {
		printf("Inserisci il numero degli elementi > \n");
		EsitoLettura = scanf("%d", &NumeroElem);
		AcqErr = EsitoLettura != 1 || NumeroElem < 1 || NumeroElem >= (INT_MAX / 4);
		if (AcqErr)
			printf("Errore !\n");
		while (getchar() != '\n');
	} while (AcqErr);
	
	ValoriOrdinati = (int *)calloc(NumeroElem, sizeof(int));
	if (ValoriOrdinati != NULL) {
		srand(time(NULL));
		for (Contatore = 1; (Contatore <= NumeroElem); Contatore++) {
			Valore = LIMITE_INF + rand() % (NumeroElem * NumeroElem);
			ValoriOrdinati[Contatore] = Valore;
			InserisciInPila(&Cima, Valore);
		}
		if (RimuoviDaPila(&Cima) != NULL) {
			HeapSort(ValoriOrdinati, NumeroElem);
			VisitaArray(ValoriOrdinati, NumeroElem);
		}
		else
			printf("NOP\n");

	}
	else { 
		printf("Errore, puntatore a NULL ! \n");
		exit(-1);
	}

	free(Cima);

	return (0);
}

void InserisciInPila(PilaDataSens_t **Cima, int DatoSens) {
	
	PilaDataSens_t *NuovoElem = (PilaDataSens_t *)malloc(sizeof(PilaDataSens_t));
	NuovoElem->Valore = DatoSens;
	NuovoElem->Succ = *Cima;
	*Cima = NuovoElem;
}

PilaDataSens_t *RimuoviDaPila(PilaDataSens_t **Cima) {

	PilaDataSens_t *ElemRim = *Cima;
	if (*Cima != NULL) 
		*Cima = ElemRim->Succ;
	return (ElemRim);
}

void HeapSort(int *DatiSensori, int NumeroElementi) {
	
	int sx, dx, tmp;

	for (sx = NumeroElementi / 2; (sx >= 1); sx--)
		SetacciaHeap(DatiSensori, sx, NumeroElementi);
	for (dx = NumeroElementi; (dx > 1); dx--) {
		tmp = DatiSensori[1];
		DatiSensori[1] = DatiSensori[dx];
		DatiSensori[dx] = tmp;
		SetacciaHeap(DatiSensori, 1, dx - 1);
	}

}

void SetacciaHeap(int *DatiSensori, int sx, int dx) {

	int NuovoElem, i, j;

	for (NuovoElem = DatiSensori[sx], i = sx, j = 2 * i; (j <= dx);) {
		if ((j < dx) && DatiSensori[j + 1] > DatiSensori[j])
			j++;
		if (NuovoElem < DatiSensori[j]) {
			DatiSensori[i] = DatiSensori[j];
			i = j;
			j = 2 * i;
		}
		else
			j = dx + 1;
	}
	if (i != sx)
		DatiSensori[i] = NuovoElem;
}

void VisitaArray(int *DatiSensori, int NumeroElementi) {
	
	int i;

	for (i = 1; (i <= NumeroElementi); i++)
		printf("%d\n", DatiSensori[i]);

}




