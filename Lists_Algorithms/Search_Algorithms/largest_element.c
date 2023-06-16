/*
*
* @author Elia Renzoni
* @date 16/06/2023
* @brief restituisci il K-esimo elemento piu' grande di una data sequenza(array) e nuovi numeri inseriti
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 300

typedef struct coda {
  int val_elementi;
  struct coda *succ;
} coda_t;

int *crea_prima_sequenza(int);
void inserisci_in_coda(coda_t **, coda_t **, int);
int cerca_elemento_maggiore(int, coda_t *);

int main(void) {
  coda_t *uscita = NULL, *ingresso = NULL;
  int acq_err, *prima_sequenza, elem_prima_seq, elem_nuovi_ins, elemento_ricercare;
  int contatore;

  do {
    printf("Inserisci i valori > \n");
    scanf("%d", &elem_prima_seq);
    scanf("%d", &elem_nuovi_ins);
    scanf("%d", &elemento_ricercare);
    acq_err = elem_prima_seq < 1 || elem_nuovi_ins < 1 || elemento_ricercare < 1;
    if (acq_err)
      printf("Errore !\n");
    while (getchar() != '\n');
  } while (acq_err);

  prima_sequenza = crea_prima_sequenza(elem_prima_seq);
  for (contatore = 0; (contatore < elem_prima_seq); contatore++) {
    inserisci_in_coda(&uscita, &ingresso, prima_sequenza[contatore]);
  }
  srand(time(NULL));
  for (contatore = 0; (contatore < elem_nuovi_ins); contatore++)
    inserisci_in_coda(&uscita, &ingresso, rand() % MAX_VALUE);
  printf("%d maggiore : %d \n", elemento_ricercare, cerca_elemento_maggiore(elemento_ricercare, uscita));
  return (0);
}

int *crea_prima_sequenza(int numero_elem) {
  int *primo_array = (int *)malloc(sizeof(int) * numero_elem);
  int contatore, valore;

  srand(time(NULL));
  for (contatore = 0; (contatore < numero_elem); contatore++) {
    valore = rand() % MAX_VALUE;
    primo_array[contatore] = valore;
  }
  return (primo_array);
}

void inserisci_in_coda(coda_t **uscita, coda_t **ingresso, int valore_ins) {
  coda_t *nuovo_elem = (coda_t *)malloc(sizeof(int));
  nuovo_elem->val_elementi = valore_ins;
  nuovo_elem->succ = NULL;
  if (*ingresso != NULL)
    (*ingresso)->succ = nuovo_elem;
  else
    *uscita = nuovo_elem;
  *ingresso = nuovo_elem;
}

int cerca_elemento_maggiore(int max_valore, coda_t *uscita) {
  int elem_maggiore, contatore;
  coda_t *elem;

  for (elem = uscita, contatore = 0; (elem != NULL && contatore < max_valore); elem = elem->succ, contatore++) {
    elem_maggiore = elem->val_elementi;
  }
  return (elem_maggiore);
}
