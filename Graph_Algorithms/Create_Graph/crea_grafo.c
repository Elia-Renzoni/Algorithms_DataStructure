/*
*  @author Elia Renzoni
*  @date 16/06/2023
*  @brief algoritmo per la creazione di un Grafo - Liste di Adiacenza
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOP 0

typedef struct vertici {
  int chiave;
  struct vertici *vertice_succ;
  struct archi *testa_lista;
} vertici_t;

typedef struct archi {
  struct vertici *vertice;
  struct archi *arco_succ;
} archi_t;

void creazione_lista_primaria(vertici_t **, int);
void creazione_lista_secondaria(archi_t **, int);
int cerca_valore_corretto(vertici_t *, int);
void visita_grafo_naive(vertici_t *);

int main(int argc, char** argv) {
  vertici_t *testa_lista_primaria = NULL;
  vertici_t *vertice;
  archi_t *testa_lista_secondaria = NULL;
  int valore, numero_vertici, numero_archi_uscenti, contatore;

  printf("Inserisci il numero di vertici > \n");
  scanf("%d", &numero_vertici);
  srand(time(NULL));
  for (contatore = 0; (contatore < numero_vertici); contatore++) {
    valore = rand() % 50;
    creazione_lista_primaria(&testa_lista_primaria, valore);
  }
  for (vertice = testa_lista_primaria; (vertice != NULL); vertice = vertice->vertice_succ) {
    printf("Inserisci il numero degli archi uscenti per vertice > \n");
    scanf("%d", &numero_archi_uscenti);

    for (contatore = 0; (contatore < numero_archi_uscenti); contatore++) {
      valore = rand() % 50;
      if (cerca_valore_corretto(testa_lista_primaria, valore) != NOP) {
        creazione_lista_secondaria(&testa_lista_secondaria, valore);
      }
      vertice->testa_lista = testa_lista_secondaria;
    }
    testa_lista_secondaria = NULL;
  }
  visita_grafo_naive(testa_lista_primaria);
  return (0);
}

void creazione_lista_primaria(vertici_t **testa_lista, int valore) {
  vertici_t *nuovo_vertice, *vertice_gen, *vertice_prec;
  for (vertice_gen = *testa_lista; 
              (vertice_gen != NULL); 
                    vertice_prec = vertice_gen, vertice_gen = vertice_gen->vertice_succ);
  if (vertice_gen == NULL) {
    nuovo_vertice = (vertici_t *)malloc(sizeof(vertici_t));
    nuovo_vertice->chiave = valore;
    nuovo_vertice->vertice_succ = NULL;
    nuovo_vertice->testa_lista = NULL;
    if (vertice_gen == *testa_lista)
      *testa_lista = nuovo_vertice;
    else
      vertice_prec->vertice_succ = nuovo_vertice;
  }
}

int cerca_valore_corretto(vertici_t *vertici, int val_cerc) {
  vertici_t *elem;
  for (elem = vertici; (elem != NULL && elem->chiave != val_cerc); elem = elem->vertice_succ) 
  return ((elem != NULL)? 1 : 0);
}

void creazione_lista_secondaria(archi_t **testa_lista, int valore) {
  archi_t *arco_gen, *nuovo_arco, *arco_prec;
  for (arco_gen = *testa_lista; 
                  (arco_gen != NULL); 
                        arco_prec = arco_gen, arco_gen = arco_gen->arco_succ);
  if (arco_gen == NULL) {
    nuovo_arco = (archi_t *) malloc(sizeof(archi_t));
    nuovo_arco->vertice->chiave = valore;
    nuovo_arco->arco_succ = NULL;
    if (arco_gen == *testa_lista)
      *testa_lista = nuovo_arco;
    else
      arco_prec->arco_succ = nuovo_arco;
  }
}

void visita_grafo_naive(vertici_t *testa_lista) {
  vertici_t *elem;
  archi_t *arco;
  for (elem = testa_lista; (elem != NULL); elem = elem->vertice_succ) {
    printf("%d \t", elem->chiave);
    for (arco = elem->testa_lista; (arco != NULL); arco = arco->arco_succ)
      printf("%d \t", arco->vertice->chiave);
    printf("\n");
  }
}
