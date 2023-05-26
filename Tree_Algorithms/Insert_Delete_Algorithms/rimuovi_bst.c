/*
 *
 *	@author Elia Renzoni
 *	@date 26/05/2023
 *	@brief creare un albero bst, chiedere all'utente che operazione svolgere e salvarle in uno stack, leggere lo stack e effetturare l'inserimento e rimozione
 *	nell'albero bst. 
 *
 * */


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INSERT 'i'
#define RIMUOVI 'r'

typedef struct {
	char operazione;
	int valore;
} op_t;

typedef struct stack {
	op_t operazione;
	struct stack *successivo;
} stack_t;

typedef struct bst {
	int chiave;
	struct bst *figlio_sx, *figlio_dx;
} bst_t;

op_t *crea_mem_operazioni(int);
void crea_stack(stack_t **, op_t);
stack_t *rimuovi_elem_stack(stack_t **);
int crea_albero_bst(bst_t **, int);
int rimuovi_albero_bst(bst_t **, int);
void visita_ordine_anticipato(bst_t *);

int main(void) {

	stack_t *cima = NULL, *elem = NULL;
	bst_t *radice = NULL;
	int valore, numero_elementi, contatore, esito_lettura, acquisizione_errata, numero_op, esito_op;
	op_t *operazione = NULL;

	do {
		printf("Inserisci il numero degli elementi > \n");
		esito_lettura = scanf("%d", &numero_elementi);
		printf("Inserisci le operazioni da svolgere > \n");
		esito_lettura = scanf("%d", &numero_op);
		operazione = crea_mem_operazioni(numero_op);
		acquisizione_errata = esito_lettura != 1 || numero_elementi < 1 || numero_elementi < (INT_MAX / 4) || numero_op < 1;
		if (acquisizione_errata) {
			printf("Errore !\n");
			free(operazione);
		}
		while (getchar() != '\n');
	} while (acquisizione_errata);

	srand(1);
	for (contatore = 0; (contatore < numero_elementi); contatore++) {
		valore = rand() % (numero_elementi * numero_elementi);
		esito_op = crea_albero_bst(&radice, valore);
	}
	visita_ordine_anticipato(radice);

	for (contatore = 0; (contatore < numero_op); contatore++)
		crea_stack(&cima, operazione[contatore]);

	for (contatore = 0; (contatore < numero_op); contatore++) {
		elem = rimuovi_elem_stack(&cima);
		if (elem->operazione.operazione == INSERT) {
			esito_op = crea_albero_bst(&radice, elem->operazione.valore);
			visita_ordine_anticipato(radice);
		} else {
			esito_op = rimuovi_albero_bst(&radice, elem->operazione.valore);
			visita_ordine_anticipato(radice);
		}
		free(elem);
	}

	printf("%d\n", esito_op);

	return (0);

}


op_t *crea_mem_operazioni(int numero_op) {

	op_t *operazioni = (op_t *)calloc(numero_op, sizeof(op_t));
	op_t valori;
	int contatore = 0, esito_lettura, acquisizione_errata;

	while (contatore < numero_op) {
		do {
			printf("Inserisci l'operazione > \n");
			esito_lettura = scanf("%c", &valori.operazione);
			esito_lettura += scanf("%d", &valori.valore);
			acquisizione_errata = esito_lettura != 2;
			if (acquisizione_errata)
				printf("Errore !\n");
			while (getchar() != '\n');
		} while (acquisizione_errata);
		operazioni[contatore] = valori;
		contatore++;
	}

	return (operazioni);

}

int crea_albero_bst(bst_t **radice, int valore) {

	int esito_operazione;
	bst_t *nuovo_nodo, *nodo, *nodo_padre;

	for (nodo_padre = nodo = *radice; 
			(nodo != NULL && nodo->chiave != valore); 
	     nodo_padre = nodo, nodo = (valore < nodo->chiave)? nodo->figlio_sx : nodo->figlio_dx);

	if (nodo != NULL && nodo->chiave == valore)
		esito_operazione = 0;
	else {
		esito_operazione = 1;
		nuovo_nodo = (bst_t *)malloc(sizeof(bst_t));
		nuovo_nodo->chiave = valore;
		nuovo_nodo->figlio_sx = nuovo_nodo->figlio_dx = NULL;
		if (nodo == *radice)
			*radice = nuovo_nodo;
		else
			if (valore < nodo_padre->chiave)
				nodo_padre->figlio_sx = nuovo_nodo;
			else
				nodo_padre->figlio_dx = nuovo_nodo;
	}

	return (esito_operazione);

}

void crea_stack(stack_t **cima, op_t coppia_ins) {

	stack_t *nuovo_elem = (stack_t *)malloc(sizeof(stack_t));
	nuovo_elem->operazione = coppia_ins;
	nuovo_elem->successivo = *cima;
	*cima = nuovo_elem;

}

stack_t *rimuovi_elem_stack(stack_t **cima) {

	stack_t *elem_r = *cima;
	if (*cima != NULL) 
		*cima = elem_r->successivo;
	
	return (elem_r);

}

int rimuovi_albero_bst(bst_t **radice, int val_rm) {

	int esito_operazione;
	bst_t *nodo, *nodo_padre, *nodo_sost;

	for (nodo_padre = nodo = *radice; 
			(nodo != NULL && nodo->chiave != val_rm);
		nodo_padre = nodo, nodo = (val_rm  < nodo->chiave)? nodo->figlio_sx : nodo->figlio_dx);

	if (nodo == NULL)
		esito_operazione = 0;
	else {
		esito_operazione = 1;
		if (nodo->figlio_sx == NULL) {
			if (nodo == *radice)
				*radice = nodo->figlio_dx;
			else
				if (val_rm < nodo_padre->chiave)
					nodo_padre->figlio_sx = nodo->figlio_dx;
				else 
					nodo_padre->figlio_dx = nodo->figlio_dx;
		}
		else {
			if (nodo->figlio_dx == NULL) {
				if (nodo == *radice)
					*radice = nodo->figlio_sx;
				else 
					if (val_rm < nodo_padre->chiave)
						nodo_padre->figlio_sx = nodo->figlio_sx;
					else
						nodo_padre->figlio_dx = nodo->figlio_sx;
			}
			else {
				nodo_sost = nodo;
				for (nodo_padre = nodo_sost, nodo = nodo_sost->figlio_sx; 
						(nodo->figlio_dx != NULL); 
				     nodo_padre = nodo, nodo = nodo->figlio_dx);
				nodo_sost->chiave = nodo->chiave;
				if (nodo_padre == nodo_sost)
					nodo_padre->figlio_sx = nodo->figlio_sx;
				else
					nodo_padre->figlio_dx = nodo->figlio_sx;
			}
		}
		free(nodo);
	}
	
	return (esito_operazione);

}

void visita_ordine_anticipato(bst_t *radice) {

	if (radice != NULL) {
		printf("%d\n", radice->chiave);
		visita_ordine_anticipato(radice->figlio_sx);
		visita_ordine_anticipato(radice->figlio_dx);
	}

}
