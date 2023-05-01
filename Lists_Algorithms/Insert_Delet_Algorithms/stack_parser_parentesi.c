/*
*
* @author Elia Renzoni
* @date 01/05/2023
* @brief data una sequenza di parentesi e caricata in una pila, determinare se la sequenza e' valida o meno - () true (} false
*
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX_PARENTESI   6
#define TONDA_APRI     '('
#define TONDA_CHIUDI   ')'
#define QUADRA_APRI    '['
#define QUADRA_CHIUDI  ']'
#define GRAFFA_APRI    '{'
#define GRAFFA_CHIUDI  '}'

enum {
  falso,
  vero
};

typedef struct stack {
  char          parentesi;
  struct stack *successivo;
} stack_t;

void     creazione_stack(stack_t **, char);
void     mostra_stack(stack_t *);
int      parsing_parentesi(stack_t **);

int main(void) {

  stack_t *cima = NULL;
  char    parentesi[] = {'(', ')', '{', '}', '[', ']'}, valore_da_caricare;
  int     contatore, numero_acquisito, indice, controllo_parentesi;

  printf("Inserisci un numero - indica quante parentesi caricare nella pila - \n");
  scanf("%d", &numero_acquisito);

  srand(1);
  for (contatore = 0; (contatore < numero_acquisito); contatore++) {
    indice = rand() % MAX_PARENTESI;
    valore_da_caricare = parentesi[indice];
    creazione_stack(&cima, valore_da_caricare);
  }

  printf("Ecco la disposizione delle parentesi > \n");
  mostra_stack(cima);

  printf("Distruzione della Pila e Parsing delle Parentesi\n");
  for (contatore = 0; (contatore < numero_acquisito); contatore++) {
    controllo_parentesi = parsing_parentesi(&cima);
    if (controllo_parentesi == falso)
      printf("Coppia Non valida !\n");
    else
      printf("Coppia Valida !\n");
  }

  return (0);

}

/*
* @brief creazione di uno stack - contenente delle parentesi
*
*/
void creazione_stack(stack_t **cima, char parentesi) {

  stack_t *nuovo_oggetto = (stack_t *)malloc(sizeof(stack_t));
  nuovo_oggetto->parentesi = parentesi;
  nuovo_oggetto->successivo = *cima;
  *cima = nuovo_oggetto;

}

/*
* @brief algoritmo che mostra il contenuto della pila
*
**/
void mostra_stack(stack_t *cima) {

  stack_t *oggetto_pila;

  for (oggetto_pila = cima; (oggetto_pila != NULL); oggetto_pila = oggetto_pila->successivo)
      printf("%c\n", oggetto_pila->parentesi);


}

/*
* @brief Algoritmo di rimozione di elementi da una pila e parsing delle parentesi
*
*/
int parsing_parentesi(stack_t **cima) {

  stack_t *oggetto_pila = *cima;
  int      esito_parsing;

  if (*cima != NULL) {
    *cima = (*cima)->successivo;
    switch (oggetto_pila->parentesi) {
      case TONDA_APRI:
        if ((*cima)->parentesi == TONDA_CHIUDI)
          esito_parsing = vero;
        else
          esito_parsing = falso;
        break;
      case QUADRA_APRI:
        if ((*cima)->parentesi == QUADRA_CHIUDI)
          esito_parsing = vero;
        else
          esito_parsing = falso;
        break;
      case GRAFFA_APRI:
        if ((*cima)->parentesi == GRAFFA_APRI)
          esito_parsing = vero;
        else
          esito_parsing = falso;
        break;
    }
  }

  free(oggetto_pila);

}
