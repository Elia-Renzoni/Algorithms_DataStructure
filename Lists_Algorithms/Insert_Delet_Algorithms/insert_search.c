/*
*
* @author Elia Renzoni
* @date 01/05/2023
* @brief Inserimento in una coda di una coppia di valori, e ricerca in essa.
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMITE_MIN     0
#define LIMITE_MAX     3
#define MAX_NUMERO_STR 5

typedef struct {
  int     numero;
  char    stringa[MAX_NUMERO_STR];
} valori_t;

typedef struct coda {
  valori_t    valore;
  struct coda *successivo;
} coda_t;

void    creazione_coda(coda_t **, coda_t **, valori_t);
void    mostra_coda(coda_t *);
coda_t *ricerca_in_coda(coda_t *, int, char stringa[]);

int main(void) {

  coda_t  *uscita = NULL, *ingresso = NULL, *elemento_cercato;
  int      numero_acquisito, contatore, indice, elemento_rand, numero_da_ricercare;
  valori_t accesso;
  char     alfabeto[] = "abcdefghilmnopqrstuvz", stringa_da_ricercare[MAX_NUMERO_STR];

  printf("Inserisci un numero > \n");
  scanf("%d", &numero_acquisito);

  srand(time(NULL));
  for (contatore = 0; (contatore < numero_acquisito); contatore++) {
    accesso.numero = LIMITE_MIN + rand() % (LIMITE_MAX * numero_acquisito);
    for (indice = 0; (indice < MAX_NUMERO_STR); indice++) {
      elemento_rand = rand() % 26;
      accesso.stringa[indice] = alfabeto[elemento_rand];
    }
    creazione_coda(&uscita, &ingresso, accesso);
  }

  printf("Elementi della Coda > \n");
  mostra_coda(uscita);

  printf("Inserisci un valore da cercare, un numero intero e una stringa");
  printf("Inserisci un numero intero >\n");
  scanf("%d", &numero_da_ricercare);
  printf("Inserisci una stringa > \n");
  scanf("%5s", stringa_da_ricercare);
  elemento_cercato = ricerca_in_coda(uscita, numero_da_ricercare, stringa_da_ricercare);

  if (elemento_cercato != NULL)
    printf("Trovato !\n");
  else
    printf("Non trovato !\n", );



  return (0);

}

/*
* @brief algoritmo per creare una coda - ordine FIFO
*
**/
void creazione_coda(coda_t **uscita, coda_t **ingresso, valori_t accesso) {

  coda_t *nuovo_elemento = (coda_t *)malloc(sizeof(coda_t));
  nuovo_elemento->valore.numero = accesso.numero;
  nuovo_elemento->valore.stringa = accesso.stringa;
  nuovo_elemento->successivo = NULL;

  if (*ingresso != NULL)
    (*ingresso)->successivo = nuovo_elemento;
  else
    *uscita = nuovo_elemento;

  *ingresso = nuovo_elemento;

}

/*
* @brief algoritmo per mostrare il contenuto della coda
*
**/
void mostra_coda(coda_t *uscita) {

  coda_t *oggetto_lista;

  for (oggetto_lista = uscita; (oggetto_lista != NULL); oggetto_lista = oggetto_lista->successivo)
      printf("%d%s", oggetto_lista->valore.numero, oggetto_lista->valore.stringa);


}

/*
* @brief algoritmo di riceca in una lista
*
**/
coda_t *ricerca_in_coda(coda_t *uscita, int numero_ricerca, char stringa_ricerca[]) {

  coda_t  *oggetto_lista;
  valori_t accesso;

  for (oggetto_lista = uscita;
      ((oggetto_lista != NULL) && (oggetto_lista->valore.numero != numero_ricerca) && (oggetto_lista->valore.stringa != stringa_ricerca[]))
      oggetto_lista = oggetto_lista->successivo)

  return (oggetto_lista);
  

}
