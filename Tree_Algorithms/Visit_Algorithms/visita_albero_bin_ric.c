/*
*
* @author Elia Renzoni
* @date 02/05/2023
* @brief Algoritmi di Visita - ord. Anticipato - ord. Posticipato - ord. Simmetrico. di un albero binario di ricerca
*
**/

#include <stdio.h>
#include <stdlib.h>

enum {
  ordine_ant,
  ordine_simm,
  ordine_post
};

typedef struct tree {
  int          valore;
  struct tree *figlio_sx, *figlio_dx;
} tree_t;

void creazione_albero_bin_ric(tree_t **, int);
void visita_ordine_anticipato(tree_t *);
void visita_ordine_simmetrico(tree_t *);
void visita_ordine_posticipato(tree_t *);

int main(void) {

  tree_t *radice_albero_bin = NULL;
  int     valore_inserire, contatore, numero_nodi, mod_visita;

  printf("Inserisci il numero di Nodi > \n");
  scanf("%d", &numero_nodi);
  srand(1);
  for (contatore = 0, valore_inserire = rand() % numero_nodi; (contatore < numero_nodi); contatore++, valore_inserire = rand() % numero_nodi)
    creazione_albero_bin_ric(&radice_albero_bin, valore_inserire);

  printf("Inserisci la modalita di visita > \n");
  printf("[0] Anticipato, [1] Simmetrico, [2] Posticipato \n");
  scanf("%d", &mod_visita);
  switch (mod_visita) {
    case ordine_ant:
      visita_ordine_anticipato(radice_albero_bin);
      break;
    case ordine_simm:
      visita_ordine_simmetrico(radice_albero_bin);
      break;
    case ordine_post:
      visita_ordine_posticipato(radice_albero_bin);
      break;
    default:
      printf("Errore !\n");
      break;
  }

  return (0);

}

/*
*
* @brief Algoritmo di Creazione di un Albero Binario di Ricerca
*
**/
void creazione_albero_bin_ric(tree_t **radice_albero, int valore_inserire) {

  tree_t *nuovo_nodo, *nodo, *nodo_padre;

  for (nodo_padre = nodo = *radice_albero;
        ((nodo != NULL) && (nodo->valore != valore_inserire));
      nodo_padre = nodo, nodo = (valore_inserire < nodo->valore)? nodo->figlio_sx : nodo->figlio_dx);

  if (nodo == NULL) {
    nuovo_nodo = (tree_t *)malloc(sizeof(tree_t));
    nuovo_nodo->valore = valore_inserire;
    nuovo_nodo->figlio_sx = NULL;
    nuovo_nodo->figlio_dx = NULL;

    if (nodo == *radice_albero)
      *radice_albero = nuovo_nodo;
    else {
      if (valore_inserire < nodo_padre->valore)
          nodo_padre->figlio_sx = nuovo_nodo;
      else
          nodo_padre->figlio_dx = nuovo_nodo;
    }
  }


}

/*
* @brief Algoritmo di Visita in Ordine Anticipato
*
**/
void visita_ordine_anticipato(tree_t *radice) {

  if (radice != NULL) {
    printf("%d\n", radice->valore);
    visita_ordine_anticipato(radice->figlio_sx);
    visita_ordine_anticipato(radice->figlio_dx);
  }

}

/*
*
* @brief Algoritmo di Visita in Ordine Simmetrico
*
**/
void visita_ordine_simmetrico(tree_t *radice) {

  if (radice != NULL) {
    visita_ordine_simmetrico(radice->figlio_sx);
    printf("%d\n", radice->valore);
    visita_ordine_simmetrico(radice->figlio_dx);
  }

}

/*
*
* @brief Algoritmo di Visita in Ordine Posticipato
*
***/
void visita_ordine_posticipato(tree_t *radice) {

  if (radice != NULL) {
    visita_ordine_posticipato(radice->figlio_sx);
    visita_ordine_posticipato(radice->figlio_dx);
    printf("%d\n", radice->valore);
  }

}
