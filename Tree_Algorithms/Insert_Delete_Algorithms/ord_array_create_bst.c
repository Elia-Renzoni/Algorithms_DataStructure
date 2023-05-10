/*
*
* @author Elia Renzoni
* @date 10/05/2023
* @brief leggere dei valori da un file e memorizzarli in un array, , e mapparli su un albero binario.
*
**/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct bst {
  int         chiavi;
  struct bst *figlio_sx, *figlio_dx;
} bst_t;

void   disposizione_array(int *, int *);
void   selectsort(int array[], int *);
bst_t *avvia_creazione_bst(void);
void   creazione_bst(bst_t **, int);
void   visita_ordine_simmetrico(bst_t *);

int main(void) {

  bst_t *radice;
  int   *array, contatore, numero_elementi;

  printf("Disposizione Array \n");
  disposizione_array(array, &numero_elementi);
  contatore = 0;
  while (contatore < numero_elementi) {
    printf("%d\n", array[contatore]);
    contatore++;
  }

  radice = avvia_creazione_bst();
  printf("Visita in Ordine Anticipato > \n");
  visita_ordine_simmetrico(radice);

  return (0);

}

/*
*
* @brief disposizione valori degli elementi secondo la visita in ordine simmetrico
*
*/
void disposizione_array(int *array, int *numero_elementi) {

  FILE *database;
  int   numero_inserire, contatore;

  database = fopen("database.txt", "w");
  if (database != NULL) {
    printf("Inserisci il numero di elementi dell'array > \n");
    scanf("%d", numero_elementi);
    srand(time(NULL));
    for (contatore = 0; (contatore < *numero_elementi); contatore++) {
      numero_inserire = rand() % *numero_elementi;
      fprintf(database, "%d\n", numero_inserire);
    }
    fclose(database);
    database = fopen("database.txt", "r");
    if (database != NULL) {
      array = (int *)calloc(*numero_elementi, sizeof(int));
      for (contatore = 0; (contatore < *numero_elementi); contatore++)
          fscanf(database, "%d", &array[contatore]);
      selectsort(array, numero_elementi);
      fclose(database);
    }
    else
      printf("Impossibile aprire il file ! \n");
  }
  else
    printf("Impossibile Aprire il File ! \n");

}


/*
* @brief SelecSort
*
**/
void selectsort(int array[], int *numero_elementi) {

  int valore_minimo, indice_valore_minimo, i, j;

  for (i = 0; (i < *numero_elementi - 1); i++) {
    for (valore_minimo = array[i], indice_valore_minimo = i, j = i + 1; (j < *numero_elementi); j++) {
      if (array[j] < valore_minimo) {
        valore_minimo = array[j];
        indice_valore_minimo = j;
      }
    }
    if (indice_valore_minimo != i) {
      array[indice_valore_minimo] = array[i];
      array[i] = valore_minimo;
    }
  }

}

/*
* @brief creazione albero binario di riceca
*
**/
bst_t *avvia_creazione_bst(void) {

  FILE  *database;
  bst_t *radice = NULL;
  int    valore, valore_rtn;

  database = fopen("database.txt", "r");
  if (database != NULL) {
    for (valore_rtn = fscanf(database, "%d", &valore); (valore_rtn != EOF); valore_rtn = fscanf(database, "%d", &valore))
      creazione_bst(&radice, valore);
    fclose(database);
  }

  return (radice);

}

void creazione_bst(bst_t **radice, int chiave) {

  bst_t *nodo_n, *nodo_padre, *nuovo_nodo;

  for (nodo_padre = nodo_n = *radice;
          ((nodo_n != NULL) && (nodo_n->chiavi != chiave));
       nodo_padre = nodo_n, nodo_n = (chiave < nodo_n->chiavi)? nodo_n->figlio_sx : nodo_n->figlio_dx);

  if (nodo_n == NULL) {
    nuovo_nodo = (bst_t *)malloc(sizeof(bst_t));
    nuovo_nodo->chiavi = chiave;
    nuovo_nodo->figlio_sx = nuovo_nodo->figlio_dx = NULL;
    if (nodo_n == *radice) {
      *radice = nuovo_nodo;
    }
    else {
      if (chiave < nodo_padre->chiavi)
        nodo_padre->figlio_sx = nuovo_nodo;
      else
        nodo_padre->figlio_dx = nuovo_nodo;
    }
  }

}

/*
* @brief Visita in Ordine Anticipato
*
**/
void visita_ordine_simmetrico(bst_t *radice) {

  if (radice != NULL) {
    visita_ordine_simmetrico(radice->figlio_sx);
    printf("%d\n", radice->chiavi);
    visita_ordine_simmetrico(radice->figlio_dx);
  }

}
