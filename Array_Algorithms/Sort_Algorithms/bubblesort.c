/**
 * @file bubblesort.c
 * @author Elia Renzoni (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-26
 * 
 * @copyright Copyright (c) 2023
 * 
 * Problem : an Implementation of bubblesort algorithm 
 * 
 * 
 */

#include <stdio.h>

#define  ARR_LENGHT  9

void bubblesort(int array_non_ord[], int num_element);

int main(void) {

    int array[] = {12, 3, 5, 7, 64, 2, 9, 11, 10};
    int index = 0;
    int numero_elementi = ARR_LENGHT;

    printf("Array non orded > \n");
    while (index < numero_elementi) {
        printf("%d\n", array[index]);
        index++;
    }

    bubblesort(array, numero_elementi);

    printf("Array ord. \n");
    index = 0;
    while (index < numero_elementi) {
        printf("%d\n", array[index]);
        index++;
    }


    return (0);

}

/**
 * @brief bubblesort algorithm => T(n) = O(n^2)
 * 
 */
void bubblesort(int array[], int num_elements) {

    int tmp, i, j;

    for (i = 1; (i < num_elements); i++) {

        for (j = num_elements - 1; (j >= i); j--)
        
            if (array[j] < array[j - 1]) {
                tmp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = tmp;
            }

    }

}

