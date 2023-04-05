/**
 * @file heap_sort.c
 * @author Elia Renzoni (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 * Problema : Implementazione dell'Algoritmo Heap-Sort
 * 
 */



#include <stdio.h>

#define  MAX_ELEMENTS  12

void heap_sort(int array[], int numero_elementi);
void crea_heap(int array[], int sx, int dx);

int main(void) {

    int numeri[] = {2, 10, 5, 20, 55, 4, 7, -50, 32, 1, 67, 8};
    int numero_elementi = MAX_ELEMENTS;
    int cnt = 0;

    printf("Array non Ordinato > \n");
    while (cnt < MAX_ELEMENTS) {
        printf("%d\n", numeri[cnt]);
        cnt++;
    }

    heap_sort(numeri, numero_elementi);

    printf("Array Ordinato > \n");
    cnt = 0;
    while (cnt < MAX_ELEMENTS) {
        printf("%d\n", numeri[cnt]);
        cnt++;
    }

    return (0);
}


/**
 * @brief heap-sort
 * 
 */
void heap_sort(int numeri[], int numero_elementi) {

    int index_sx,
        index_dx,
        tmp;

    /* prima fase : creazione max-heap */
    for (index_sx = numero_elementi / 2; (index_sx >= 1); index_sx--)
        crea_heap(numeri, index_sx, numero_elementi);

    /* seconda fase : ordinamento dell'array */
    for (index_dx = numero_elementi; (index_dx > 1); index_dx--) {
        tmp = numeri[1];
        numeri[1] = numeri[index_dx];
        numeri[index_dx] = tmp;

        crea_heap(numeri, 1, index_dx - 1);
    }


}

/**
 * @brief funzione che fa rispettare le prop. del Max - Heap
 * 
 */
void crea_heap(int numeri[], int sx, int dx) {

    int valore_max, i, j;

    for (valore_max = numeri[sx], i = sx, j = 2 * i; 
            (j <= dx);) {

                if ((j < dx) && (numeri[j + 1] > numeri[j]))  /* determino il maggiore tra i figli */
                    j++;

                if (valore_max < numeri[j]) {      /* confronto il maggiore tra i figli con il nodo gen. */

                    numeri[i] = numeri[j];
                    i = j;
                    j = 2 * i;
                }
                else 
                    j = dx + 1;    /* la condizione diventa falsa */

    }

    if (i != sx)
        numeri[i] = valore_max;
}