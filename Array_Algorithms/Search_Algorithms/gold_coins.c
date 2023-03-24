/**
 * @file gold_coins.c
 * @author Elia Renzoni
 * @brief 
 * @version 0.1
 * @date 2023-03-24
 * 
 * @copyright Copyright (c) 2023
 * 
 *  Problem : 
 */

#include <stdio.h>
#include <stdlib.h>

#define  LIMITE_MAX   50
#define  NOT_FOUND   -1

void sort_coins(int coins[], int num_element);
int  binary_search(int coins[], int num_element, int value_search);

int main(void) {

    int *darray,
        num_elements;
    int i, error, s_value, found;
    
    do {
        printf("Insersci il numero degli elementi > \n");
        scanf("%d", &num_elements);
        printf("Inserisci le chiavi > \n");
        darray = (int *)calloc(num_elements, sizeof(int));

        for (i = 0; (i < num_elements); i++)
            scanf("%d", &darray[i]);
        
        error = num_elements < 0 || num_elements > LIMITE_MAX;

        if (error) {
            printf("Errore ! \n");
            free(darray);
        }

        while (getchar() != '\n');

    } while (error);

    sort_coins(darray, num_elements);

    printf("Inserisci il valore da cercare > \n");
    scanf("%d", &s_value);
    found = binary_search(darray, num_elements, s_value);

    if (found != NOT_FOUND)
        printf("Elemento Presente nella posizione %d. \n", found);
    else
        printf("Elemento non trovato !\n");
    


    return (0);
}
/**
 * selecsort => g(n) = O(n^2)
 */
void sort_coins(int coins[], int num_element) {

    int i, j, min_value, index_min_value;

    for (i = 0; (i < num_element - 1); i++) {

        for (min_value = coins[i], index_min_value = i, j = i + 1; (j < num_element); j++)

            if (coins[j] < min_value) {
                min_value = coins[j];
                index_min_value = j;          
            }
        
        if (index_min_value != i) {
            coins[index_min_value] = coins[i];
            coins[i] = min_value;
        }
            
    }

}

int binary_search(int coins[], int elments, int value) {

    int isx, idx, imx;

    for (isx = 0, idx = elments - 1, imx = (idx + isx) / 2; (isx <= idx) && (coins[imx] != value); imx = (isx + idx) / 2)
        if (coins[imx] > value)
            idx = imx - 1;
        else 
            isx = imx + 1;


    return ((isx <= idx)? imx : NOT_FOUND);

}