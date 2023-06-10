/*
*
* @author Elia Renzoni
* @date 10/06/2023
* @Brief creazione di un carrello amazon, tramite Cima
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PREZZO 500

typedef struct {
  int prezzo_articolo;
  char *nome_articolo;
} prodotto_t;

typedef struct carrello {
  prodotto_t chiave;
  struct carrello *succ;
} carrello_t;

void metti_in_carrello(carrello_t **, prodotto_t);
char *genera_nome(void);
carrello_t *elimina_da_carrello(carrello_t **);
int calcola_prezzo_totale(carrello_t *);
void visualizza_carrello(carrello_t *);

int main(int argc, char **argv) {

  carrello_t *cima = NULL, *elem_elim;
  int prezzo, numero_elem, contatore;
  prodotto_t info_prodotto;

  do {
    printf("Inserisci il numero degli elementi > \n");
    scanf("%d", &numero_elem);
    if (numero_elem < 1)
      printf("Errore !\n");
    else
      break;
    while (getchar() != '\n');
  } while (numero_elem < 1);

  srand(time(NULL));
  for (contatore = 0; (contatore < numero_elem); contatore++) {
    info_prodotto.prezzo_articolo = prezzo = rand() % MAX_PREZZO;
    info_prodotto.nome_articolo = genera_nome();
    metti_in_carrello(&cima, info_prodotto);
  }

  visualizza_carrello(cima);
  elem_elim = elimina_da_carrello(&cima);
  if (elem_elim != NULL) {
    printf("Articolo %s con prezzo %d elimiato dal carrello !\n");
    free(elem_elim);
  }
  else {
    printf("NOP \n");
  }
  printf("Prezzo totale del carrello > %d \n", calcola_prezzo_totale(cima));

  return (0);
}

void metti_in_carrello(carrello_t **cima, prodotto_t info_prod) {
  carrello_t *nuovo_elem = (carrello_t *)malloc(sizeof(carrello_t));
  nuovo_elem->chiave.prezzo_articolo = info_prod.prezzo_articolo;
  nuovo_elem->chiave.nome_articolo = info_prod.nome_articolo;
  nuovo_elem->succ = *cima;
  *cima = nuovo_elem;
}

char *genera_nome(void) {
  char *nome = (char *)calloc(5, sizeof(char));
  char alfabeto[] = "abcdefghilmnopqrstuvz";
  int contatore;
  for (contatore = 0; (contatore < 5); contatore++) {
    nome[contatore] = alfabeto[rand() % 26];
  }
  return (nome);
}

carrello_t *elimina_da_carrello(carrello_t **cima) {
  carrello_t *elem_rem = *cima;
  if (*cima != NULL)
    *cima = (*cima)->succ;
  return (elem_rem);
}

int calcola_prezzo_totale(carrello_t *cima) {
  int prezzo_tot = 0;
  carrello_t *elem;
  for (elem = cima; (elem != NULL); elem = elem->succ)
    prezzo_tot += elem->chiave.prezzo_articolo;
  return (prezzo_tot);
}

void visualizza_carrello(carrello_t *cima) {
  carrello_t *elem;
  for (elem = cima; (elem != NULL); elem = elem->succ)
    printf("Prodotto %s - Prezzo %d \n", elem->chiave.nome_articolo, elem->chiave.prezzo_articolo);
}
