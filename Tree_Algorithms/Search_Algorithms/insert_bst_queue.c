/*
*
* @author Elia Renzoni
* @date 26/05/2023
* @brief crea un albero bst, ricerca un valore e stampa il percorso con i valori dei nodi che attraversa e memorizzali in una coda, poi elimianre gli elementi della coda
**/

#include <stdio.h>
#include <stdlib.h>

#define MAX_GEN 20

typedef struct coda {
  int chiave;
  struct coda *next;
} coda_t;

typedef struct bst {
  int valore;
  struct bst *sx;
  struct bst *dx;
} bst_t;

void crea_albero_bst(bst_t **, int);
void visita_simmetrica(bst_t *);
void crea_coda(coda_t **, coda_t **, int);
void mostra_coda(coda_t *);
bst_t *ricerca_bin_nodo(bst_t *, int, coda_t *, coda_t *);
coda_t *elimina_coda(coda_t **, coda_t **);

int main(void) {

  coda_t *ingresso = NULL, *uscita = NULL, *elim = NULL;
  bst_t *radice = NULL, *nodo = NULL;
  int valore, numero_elem, contatore, valore_cercare;

  printf("Inserisci il numero degli elementi > \n");
  scanf("%d", &numero_elem);
  printf("Inserisci il valore da cercare > \n");
  scanf("%d", &valore_cercare);

  srand(1);
  for (contatore = 0; (contatore < numero_elem); contatore++) {
    valore = rand() % (numero_elem * MAX_GEN);
    crea_albero_bst(&radice, valore);
  }
  visita_simmetrica(radice);
  nodo = ricerca_bin_nodo(radice, valore_cercare, &uscita, &ingresso);
  if (nodo != NULL) {
    printf("Valore trovato seguendo il percorso : \n");
    mostra_coda(uscita);
  }
  else
    printf("Valore Non trovato");

  elim = elimina_coda(&uscita, &ingresso);
  while (elim != NULL) {
    elim = elimina_coda(&uscita, &ingresso);
    free(elim);
  }

  return (0);

}

void crea_albero_bst(bst_t **radice, int valore) {

  bst_t *nodo, *nodo_padre, *nuovo_nodo;

  for (nodo_padre = nodo = *radice;
            (nodo != NULL);
      nodo_padre = nodo, nodo = (valore < nodo->valore)? nodo->sx : nodo->dx);

  if (nodo == NULL) {
    nuovo_nodo = (bst_t *)malloc(sizeof(bst_t));
    nuovo_nodo->valore = valore;
    nuovo_nodo->sx = nuovo_nodo->dx = NULL;
    if (nodo == *radice)
      *radice = nuovo_nodo;
    else
      if (valore < nodo_padre->valore)
        nodo_padre->sx = nuovo_nodo;
      else
        nodo_padre->dx = nuovo_nodo;
  }

}

void visita_simmetrica(bst_t *radice) {

  if (radice != NULL) {
    visita_simmetrica(radice->sx);
    printf("%d\n", radice->valore);
    visita_simmetrica(radice->dx);
  }

}

bst_t *ricerca_bin_nodo(bst_t *radice, int val_src, coda_t **uscita, coda_t **ingresso) {

  bst_t *nodo;

  for (nodo = radice; (nodo != NULL && nodo->valore != val_src); nodo = (val_src < nodo->valore)? nodo->sx : nodo->dx)
    crea_coda(&uscita, &ingresso, nodo->valore);

  return (nodo);

}

void crea_coda(coda_t **uscita, coda_t **ingresso, int valore) {

  coda_t *nuovo_elem = (coda_t *)malloc(sizeof(coda_t));
  nuovo_elem->chiave = valore;
  nuovo_elem->next = NULL;
  if (*ingresso != NULL)
    (*ingresso)->next = nuovo_elem;
  else
    *uscita = nuovo_elem;
  *ingresso = nuovo_elem;

}

void mostra_coda(coda_t *uscita) {

  coda_t *elem;

  for (elem = uscita; (elem != NULL); elem = elem->next)
    printf("%d\n", elem->chiave);

}

coda_t *elimina_coda(coda_t **uscita, coda_t **ingresso) {

  coda_t *elem_del = *uscita;
  if (*uscita != NULL) {
    *uscita = elem_del->next;
    if (*uscita == NULL)
      *ingresso = NULL;
  }
  return (elem_del);

}
