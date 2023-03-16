/*
 *
 *
 *
 *	Programma : Software Per il Calcolo della Sequenza di Fibonacci, calcolata iterativamente e
 *	ricorsivamente
 *	Data 16/03/2023
 *
 *
 *
 *
 * */




#include <stdio.h>
#include <limits.h>

#define FIBO_I 0
#define FIBO_R 1

int calcola_fibonacci_it(int);
int calcola_fibonacci_ri(int);

int main(void) {

	int numero_selezionato,
	    scelta_utente;
	int verifica_errori,
	    verifica_scanf;
	int seq_fibo_iter,
	    seq_fib_rico;


	do {
		printf("Inserisci un numero >= 1 > \n");
		verifica_scanf = scanf("%d", &numero_selezinato);
		printf("Calcola la Sequenza di Finbonacci Iterativamente [0] o Ricorsivamente [1] \n");
		verifica_scanf = scanf("%d", &scelta_utente);

		verifica_errori = numero_selezionato < 1 || 
				  numero_selezioanto > (INT_MAX / 2) || 
				  scelta_utente < FIBO_I || 
				  scelta_utente > FIBO_R;

		if (verifica_errori)
			printf("Errore ! \n");

		while (getchar() != '\n');

	} while (verifica_errori);


	switch (scelta_utente) {

		case FIB_I:
			seq_fibo_iter = calcola_fibonacci_it(numero_selezionato);
			printf("La sequenza di fibonacci del numero %d è %d", numero_selezionato, seq_fibo_iter);
			break;
		case FIB_R:
			seq_fib_rico = calcola_fibonacci_ri(numero_selezionato);
			printf("La sequenza di fibonacci del numero %d è %d", numero_selezionato, seq_fibo_rico);
			break;
	}



	return (0);
}

int calcola_fibonacci_it(int numero_digitato) {

	int fibonacci,
	    ultimo,
	    penultimo,
	    contatore;

	if ((numero_digitato == 1) || (numero_digitato == 2))
		fibonacci = 1;
	else
		for (ultimo = penultimo = 1, contatore = 3;
				(contatore <= numero_digitato);
		    contatore++) {

			fibonacci = ultimo + penultimo;
			penultimo = ultimo;
			ultimo = fib;
		}


	
	return (fibonacci);

}

int calcola_fibonacci_ri(int numero_digitato) {


	int fibonacci;

	if ((numero_digitato == 1) || (numero_digitato == 2))
		fibonacci = 1;
	else
		fibonacci = calcola_fibonacci_ri(numero_digitato - 1) + calcola_fibonacci_ri(n - 2);

	return (fibonacci);
}