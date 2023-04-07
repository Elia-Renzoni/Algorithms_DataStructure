/**
 * @file search_and_sort.c
 * @author Elia Renzoni 
 * @brief 
 * @version 0.1
 * @date 2023-04-04
 * 
 * @copyright Copyright (c) 2023
 * 
 * Problema : Il programma deve chiedere all'utente il numeri dei valori da ordinare, e generare n numeri pseudo-casualmente; successivamente
 * verrano ordinati in ordine crescente. Inoltre l'utente potrá ricercare dei valore all'interno - esempio k = 4, ovvero il 4 valore piú grande
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define  MAX_N_GENERABILI  10
#define  MIN_N_GENERABILI  0

void heapsort(int numeri[], int n_elementi);
void crea_heap(int numeri[], int indice_sx, int indice_dx);
int  seleziona_elemento(int numeri[], int n_elementi, int valore_da_ricercare);

int main(void) {

    int *numeri;
    int  numero_elementi,
         grad_valore_ricercare;
    int  numero_generato, i, acquisizione_errata, rtn_scanf, elemento;

    do {
        printf("Inserisci il numero dei valori da ordinare => \n");
        rtn_scanf = scanf("%d", &numero_elementi);
        printf("Inserisci il grado del valore da ricercare => \n");
        rtn_scanf = scanf("%d", &grad_valore_ricercare);

        acquisizione_errata = rtn_scanf != 1 || numero_elementi < MIN_N_GENERABILI || numero_elementi > (MAX_N_GENERABILI * numero_elementi) 
                              || grad_valore_ricercare < 1 || grad_valore_ricercare > numero_elementi;

        if (acquisizione_errata)
            printf("Errore, ripeti ! \n");

        while (getchar() != '\n');

    } while (acquisizione_errata);

    /**
     * @brief allocazione e inizializzazione
     * 
     */
    numeri = (int *)calloc(numero_elementi, sizeof(int));
    srand(1);                                                     /* imposta il seme */
    i = 0;
    while (i < numero_elementi) {
        numero_generato = rand() % (numero_elementi * MAX_N_GENERABILI);
        numeri[i] = numero_generato;
        printf("%d\n", numeri[i]);
        i++;
    }

    /**
     * @brief ordinamento array e selezione elemento
     * 
     */
    heapsort(numeri, numero_elementi);
    printf("\n Array Ordinato \n");
    i = 0;
    while (i < numero_elementi) {
        printf("%d\n", numeri[i]);
        i++;
    }
    elemento = seleziona_elemento(numeri, numero_elementi, grad_valore_ricercare);

    printf("%d elemento piu' grande > %d \n", grad_valore_ricercare, elemento);
    
    free(numeri);

    return (0);
}

/**
 * @brief heapsort
 * 
 */
void heapsort(int numeri[], int numero_elementi) {

    int indice_sx, tmp, indice_dx;

    /* creazione heap */
    for (indice_sx = numero_elementi / 2; (indice_sx >= 1); indice_sx--)
        crea_heap(numeri, indice_sx, numero_elementi);
    
    /* ordinamento e creazione heap sulla restante parte */
    for (indice_dx = numero_elementi; (indice_dx > 1); indice_dx--) {

        tmp = numeri[1];
        numeri[1] = numeri[indice_dx];
        numeri[indice_dx] = tmp;
        crea_heap(numeri, 1, indice_dx - 1);

    }

}

/**
 * @brief funzione per creare un max-heap (fa rispettare le condizioni)
 * 
 */
void crea_heap(int numeri[], int indice_sx, int indice_dx) {

    int nuovo_val, i, j;

    nuovo_val = numeri[indice_sx]; 
    i = indice_sx;
    j = 2 * i;
    while (j <= indice_dx) {
        if ((j < indice_dx) && (numeri[j + 1] > numeri[j]))
            j++;
        if (nuovo_val < numeri[j]) {
            numeri[i] = numeri[j];
            i = j;
            j = 2 * i;
        }
        else
            j = indice_dx + 1;
    }

    if (i != indice_sx)
        numeri[i] = nuovo_val;
}

/**
 * @brief selezione elemento
 * 
 */
int seleziona_elemento(int numeri[], int numero_elementi, int grado) {

    int valore_selezionato = numero_elementi - grado;

    return (numeri[valore_selezionato]);
}
