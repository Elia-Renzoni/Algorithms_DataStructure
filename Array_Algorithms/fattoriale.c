/*
 *
 *
 *
 *	Programma : Software per il Calcolo del Fattoriale ricorsivamente e iterativamente
 *	Data : 16/03/23 - Prima Esercitazione di Lab.
 *
 *
 *
 * */



#include <stdio.h>
#include <limits.h>

#define SCELTA_FATT_I 0
#define SCELTA_FATT_R 1

int fattoriale_iterativo(int);
int fattoriale_ricorsivo(int);

int main(void) {

	int                 numero_selezionato,      /* var. input  */
	                    scelta_utente;	     /* var. input  */
	int                 verifica_errori,	     /* var. lavoro */
	                    verifica_scanf;          /* var. lavoro */
	int                 fattoriale_i,	     /* var. output */
			    fattoriale_r;	     /* var. output */

	/* acquisizione e validazione input */
	do {
		printf("Inserisci un numero naturale maggiore o uguale a 1 > \n");
		verifica_scanf = scanf("%d", &numero_selezionato);
		printf("Calcola Iterativamente [0] o Ricorsivamente [1] \n");
		verifica_scanf = scanf("%d", &scelta_utente);

		verifica_errori = numero_selezionato < 1 || 
				  scelta_utente < SCELTA_FATT_I || 
				  scelta_utente > SCELTA_FATT_R || 
				  verifica_scanf != 1 || 
				  numero_selezionato > (INT_MAX / 2);

		if (verifica_errori)
			printf("Errore ! \n");
		while (getchar() != '\n');

	} while (verifica_errori);

	switch (scelta_utente) {

		case SCELTA_FATT_I:
			fattoriale_i = fattoriale_iterativo(numero_selezionato);
			printf("Il Fattoriale del Numero %d è %d \n", numero_selezionato, fattoriale_i);
			break;
		case SCELTA_FATT_R:
			fattoriale_r = fattoriale_ricorsivo(numero_selezionato);
			printf("Il Fattoriale del Numero %d è %d \n", numero_selezionato, fattoriale_r);
			break;
	}
		

	return (0);
}

/* fattoriale calcolato iterativamente */
int fattoriale_iterativo(int numero_scelto) {

	int fattoriale,
	    contatore;

	for (fattoriale = 1, contatore = 2;
		(contatore <= numero_scelto);
	     contatore++)
		fattoriale *= contatore;

	return (fattoriale);
}

/* fattoriale calcolato ricorsivamente */
int fattoriale_ricorsivo(int numero_scelto) {

	int fattoriale;

	if (numero_scelto == 1)
		fattoriale = 1;
	else
		fattoriale = numero_scelto * fattoriale_ricorsivo(numero_scelto - 1);

	return (fattoriale);
}

