/*
* @author Elia Renzoni
* @date 27/05/2023
* @brief creazione di un grafo e visita in ampiezza
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMITE_MAX 50
#define NOP        -1

typedef enum {
  bianco, nero, grigio
} colore_t;

typedef struct vertici {
  int chiave, distanza;
  struct vertici *vertice_succ;
  struct archi *archi_succ;
  struct vertici *padre;
} vertici_t;

typedef struct archi {
  struct vertici *vertice_adj;
  struct archi *arco_succ;
} archi_t;

void creazione_lista_primaria(vertici_t **, int);
int controllo_valori_lista_sec(vertici_t *);
void creazione_lista_secondaria(archi_t **, int);

int main(void) {
  vertici_t *testa_lista_p = NULL;
  vertici_t *elem_lista_p = NULL;
  archi_t *testa_lista_s = NULL;
  int valori, numero_elem_p, numero_elem_s, contatore;

  do {
    printf("Inserisci il numero dei vertici > \n");
    scanf("%d", &numero_elem_p);
    if (numero_elem_p < 1)
      printf("Errore !\n");
    while (getchar() != '\n');
  } while (numero_elem_p < 1);

  srand(time(NULL));
  for (contatore = 0; (contatore < numero_elem_p); contatore++) {
    valori = rand() % LIMITE_MAX;
    creazione_lista_primaria(&testa_lista_p, valori);
  }
  for (elem_lista_p = testa_lista_p; (elem_lista_p != NULL); elem_lista_p = elem_lista_p->vertice_succ) {
    do {
      printf("Inserisci il numero degli archi uscenti >\n");
      scanf("%d", &numero_elem_s);
      if (numero_elem_s < 0)
        printf("Errore !\n");
      while (getchar() != '\n');
    } while (numero_elem_s < 0);
    for (contatore = 0; (contatore < numero_elem_s); contatore++) {
      valori = controllo_valori_lista_sec(testa_lista_p);
      creazione_lista_secondaria(&testa_lista_s, valori);
      elem_lista_p->archi_succ = testa_lista_s;
    }
    testa_lista_s = NULL;
  }
  return (0);
}

void creazione_lista_primaria(vertici_t **testa_lista_p, int valore_vertice) {
  vertici_t *veritice_nuovo, *vertice_gen;

  for (vertice_gen = *testa_lista_p;
        (vertice_gen != NULL && vertice_gen->chiave != valore_vertice);
       vertice_gen = vertice_gen->vertice_succ);
  if (vertice_gen == NULL) {
    veritice_nuovo = (vertici_t *) malloc(sizeof(vertici_t));
    veritice_nuovo->chiave = valore_vertice;
    veritice_nuovo->padre = NULL;
    veritice_nuovo->archi_succ = NULL;
    veritice_nuovo->vertice_succ = NULL;
    if (vertice_gen == *testa_lista_p)
      *testa_lista_p = veritice_nuovo;
    else
      vertice_gen->vertice_succ = veritice_nuovo;
  }
}

int controllo_valori_lista_sec(vertici_t *testa_lista) {
  int valore_gen = rand() % LIMITE_MAX;
  int verifica_valore;
  vertici_t *vertice_gen;

  for (vertice_gen = testa_lista; (vertice_gen != NULL); vertice_gen = vertice_gen->vertice_succ) {
    if (vertice_gen->chiave == valore_gen)
      verifica_valore = 0;
    else
      verifica_valore = 1;
  }
  return ((verifica_valore == 1)? valore_gen : NOP);
}

void creazione_lista_secondaria(archi_t **testa_lista_s, int valore_uscente) {
  archi_t *arco_uscente, *nuovo_arco;

  if (valore_uscente != NOP) {
    for (arco_uscente = *testa_lista_s;
          (arco_uscente != NULL);
        arco_uscente = arco_uscente->arco_succ);
    if (arco_uscente == NULL) {
      nuovo_arco = (archi_t *) malloc(sizeof(archi_t));
      nuovo_arco->arco_succ = NULL;
      nuovo_arco->vertice_adj->chiave = valore_uscente;
      if (arco_uscente == *testa_lista_s)
        *testa_lista_s = nuovo_arco;
      else
        arco_uscente->arco_succ = nuovo_arco;
    }
  }

}
