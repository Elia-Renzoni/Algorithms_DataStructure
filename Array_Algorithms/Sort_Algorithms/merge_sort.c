/**
 * @file merge_sort.c
 * @author Elia Renzoni 
 * @brief 
 * @version 0.1
 * @date 2023-04-05
 * 
 * @copyright Copyright (c) 2023
 * 
 * Problema : Implementazione dell'algoritmo di ordinamento Merge-Sort
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#define  MAX_ELEMENTS  12

void merge_sort(int numeri[], int sx, int dx);
void merge(int numeri[], int sx, int mx, int dx);

int main(void) {

    int numeri[] = {2, 10, 5, 20, 55, 4, 7, -50, 32, 1, 67, 8};
    int sx = 0, dx = MAX_ELEMENTS - 1, cnt = 0;

    printf("Array non Ordinato > \n");
    while (cnt < MAX_ELEMENTS) {
        printf("%d\n", numeri[cnt]);
        cnt++;
    }

    merge_sort(numeri, sx, dx);    

    printf("Array Ordinato > \n");
    cnt = 0;
    while (cnt < MAX_ELEMENTS) {
        printf("%d\n", numeri[cnt]);
        cnt++;
    }

    return (0);
}

/**
 * @brief implementazione dell'algoritmo di ordinamento merge sort
 * 
 */
void merge_sort(int numeri[], int sx, int dx) {

    int mx;

    if (sx < dx) {
        mx = (sx + dx) / 2;
        merge_sort(numeri, sx, mx);
        merge_sort(numeri, mx + 1, dx);
        merge(numeri, sx, mx, dx);
    }

}

/**
 * @brief implementazione della funzione di fusione ordinata
 * 
 */
void merge(int numeri[], int sx, int mx, int dx) {

    int *appoggio, i, j, k;

    appoggio = (int *)calloc(dx + 1, sizeof(int));

    for (i = sx, j = mx + 1, k = 0; ((i <= mx) && (j <= dx)); k++) {
        if (numeri[i] <= numeri[j]) {
            appoggio[k] = numeri[i];
            i++;
        }
        else {
            appoggio[k] = numeri[j];
            j++;
        }
    }

    while (i <= mx) {
        appoggio[k] = numeri[i];
        i++;
        k++;
    }

    while (j <= dx) {
        appoggio[k] = numeri[j];
        j++;
        k++;
    }

    for (k = sx; (k <= dx); k++) 
        numeri[k] = appoggio[k - sx];

    free(appoggio);

}
