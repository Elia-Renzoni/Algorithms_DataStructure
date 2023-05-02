/*
*
* @author Elia Renzoni
* @date 02/05/2023
* @brief Algoritmo di Ricerca su un albero binario di ricerca
*
**/

#include <stdio.h>
#include <stdlib.h>

typedef struct albero_bin {
  int                valore;
  struct albero_bin *figlio_sx, *figlio_dx;
} albero_bin_t;

void          creazione_albero_bin_rice(albero_bin_t **, int);
albero_bin_t *ricerca_su_albero(albero_bin_t *, int);

int main(void) {

  albero_bin_t *radice_albero = NULL, *indirizzo_nodo;
  int           numero_nodi, contatore, valore_nodo, valore_ricercare;

  printf("Inserisci il numero di nodi > \n");
  scanf("%d", &numero_nodi);
  srand(1);
  for (contatore = 0, valore_nodo = rand() % numero_nodi; (contatore < numero_nodi); contatore++, valore_nodo = rand() % numero_nodi)
    creazione_albero_bin_rice(&radice_albero, valore_nodo);

  printf("Inserisci un valore da ricercare > \n");
  scanf("%d", &valore_ricercare);
  indirizzo_nodo = ricerca_su_albero(radice_albero, valore_ricercare);

  if (indirizzo_nodo == NULL)
    printf("Valore Non Trovato !\n");
  else
    printf("Valore Trovato ! \n");

  return (0);

}

/*
*
* @brief Algoritmo per la creazione di un albero binario di ricerca
*
**/
void creazione_albero_bin_rice(albero_bin_t **radice, int valore_nodo) {

  albero_bin_t *nuovo_nodo, *nodo_nesimo, *padre_nodo;

  for (padre_nodo = nodo_nesimo = *radice;
        ((nodo_nesimo != NULL) && (nodo_nesimo->valore != valore_nodo));
       padre_nodo = nodo_nesimo, nodo_nesimo = (valore_nodo < nodo_nesimo->valore)? nodo_nesimo->figlio_sx : nodo_nesimo->figlio_dx);

  if (nodo_nesimo == NULL) {
    nuovo_nodo = (albero_bin_t *)malloc(sizeof(albero_bin_t));
    nuovo_nodo->valore = valore_nodo;
    nuovo_nodo->figlio_dx = nuovo_nodo->figlio_sx = NULL;

    if (nodo_nesimo == *radice)
      *radice = nuovo_nodo;
    else
      if (valore_nodo < padre_nodo->valore)
        padre_nodo->figlio_sx = nuovo_nodo;
      else
        padre_nodo->figlio_dx = nuovo_nodo;
  }

}

/*
*
* @brief Algoritmo di Ricerca su una albero binario di ricerca
*
**/
albero_bin_t *ricerca_su_albero(albero_bin_t *radice, int valore_ricercare) {

  albero_bin_t *nodo_generico;

  for (nodo_generico = radice;
        (nodo_generico != NULL && nodo_generico->valore != valore_ricercare);
      nodo_generico = (valore_ricercare < nodo_generico->valore)? nodo_generico->figlio_sx : nodo_generico->figlio_dx);

  return (nodo_generico);

}
