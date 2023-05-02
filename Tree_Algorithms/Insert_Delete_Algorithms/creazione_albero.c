/*
*
* @author Elia Renzoni
* @date 02/05/2023
* @brief Algoritmo di Inserimento di nuovi valori su un albero binario di ricerca
*
**/

#include <stdio.h>
#include <stdlib.h>

enum {
  falso,
  vero
};

typedef struct tree {
  int          valore;
  struct tree  *figlio_sx, *figlio_dx;
} tree_t;

int  creazione_albero(tree_t **, int);
void visita_ordine_simmetrico(tree_t *);

int main(void) {

  tree_t *radice_albero_bin_ric = NULL;
  int     numero_generato, esito_creazione, numero_inserimenti, contatore;

  printf("Inserisci il numero di Valori da Generare ! \n");
  scanf("%d", &numero_inserimenti);
  srand(1);
  for (contatore = 0, numero_generato = rand() % numero_inserimenti; (contatore < numero_inserimenti); contatore++, numero_generato = rand() % numero_inserimenti) {
    esito_creazione = creazione_albero(&radice_albero_bin_ric, numero_generato);
    if (esito_creazione == vero)
      printf("Inserimento Effettuato ! \n");
    else
      printf("Inserimento Non Effettuato ! \n");
  }

  printf("Albero : (ordine simmetrico)\n ");
  visita_ordine_simmetrico(radice_albero_bin_ric);

  return (0);

}

/*
*
* @brief Algoritmo per la Creazione di un Albero Binario di Ricerca
*
**/
int creazione_albero(tree_t **radice_albero, int valore_da_inserire) {

  tree_t *nodo, *nuovo_nodo, *padre_nuovo_nodo;
  int     esito_inserimento;

  for (padre_nuovo_nodo = nodo = *radice_albero;
        (nodo != NULL && nodo->valore != valore_da_inserire);
       padre_nuovo_nodo = nodo, nodo = (valore_da_inserire < nodo->valore)? nodo->figlio_sx : nodo->figlio_dx);

  if (nodo != NULL)
    esito_inserimento = 0;
  else {
    esito_inserimento = 1;
    nuovo_nodo = (tree_t *)malloc(sizeof(tree_t));
    nuovo_nodo->valore = valore_da_inserire;
    nuovo_nodo->figlio_dx = nuovo_nodo->figlio_sx = NULL;

    if (nodo == *radice_albero)
      *radice_albero = nuovo_nodo;
    else {
      if (valore_da_inserire < padre_nuovo_nodo->valore)
        padre_nuovo_nodo->figlio_sx = nuovo_nodo;
      else
        padre_nuovo_nodo->figlio_dx = nuovo_nodo;
    }
  }

  return (esito_inserimento);

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
